#include "CollisionHandler.h"

#include <iostream>

void CollisionHandler::handleOutOfBoarder(std::list<std::shared_ptr<Ball>>& balls, sf::RectangleShape& window)
{
	for (auto it = balls.begin(); it != balls.end(); ) {
		if (keepBallInBoarder(*it, window)) { // Condition to delete the element
			it = balls.erase(it); // Erase returns the iterator to the next element
			break;
		}
		else {
			++it; // Only increment the iterator if you don't erase
		}
	}
}

void CollisionHandler::handleBallPlatform(std::list<std::shared_ptr<Ball>>& balls, Platform& platform)
{
	auto platform_rect = platform.getRect();

	for (auto iter = balls.begin() ; iter != balls.end() ; ++iter) {

		if (platform_rect.intersects((*iter)->getSprite().getGlobalBounds())) {

			if (platform.isSticky()) {
				std::shared_ptr<Ball> ball = *iter;
				platform.addSticky(ball);
				ball->setVelocityZero();
				balls.erase(iter);
				return;
			}

			float ballCenter = (*iter)->getSprite().getPosition().x + (*iter)->getSprite().getGlobalBounds().width / 2.0f;
			float platformLeft = platform_rect.getPosition().x;

			float collisionPoint = ballCenter - platformLeft;
			float platformWidth = platform_rect.getSize().x;
			float normalizedCollisionPoint = (collisionPoint / platformWidth) - 0.5f; // Normalize between -0.5 and 0.5

			// Calculate new velocity based on the collision point
			sf::Vector2f newVelocity = (*iter)->getVelocity();

			float angle = normalizedCollisionPoint * 2.0f * 50.0f; // Max bounce angle is 50 degrees
			float radians = angle * 3.14159f / 180.0f;
			float speed = (*iter)->getSpeed();

			newVelocity.x = std::sin(radians) * speed;
			newVelocity.y = speed * std::cos(radians);
			newVelocity.y = -newVelocity.y; // Reverse vertical direction
			
			(*iter)->setVelocity(newVelocity);

			return;
		}
	}
}

BrickInfo CollisionHandler::handleBallBrick(std::list<std::shared_ptr<Ball>>& balls, std::vector<std::shared_ptr<Brick>>& bricks)
{
	BrickInfo info;
	for (auto& ball : balls) {
		for (auto it = bricks.begin(); it != bricks.end();) {
			if (ball->getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds())) {
				resolveBallBrick(*ball, **it);
				if ((*it)->hit(1)) {
					info.cond = BrickCondition::BREAK;
					info.pos_x = (*it)->getSprite().getPosition().x;
					info.pos_y = (*it)->getSprite().getPosition().y;
					it = bricks.erase(it); // Remove brick after collision
					return info;
				}
				info.cond = BrickCondition::HIT;
				return info;
			}
			else {
				++it;
			}
		}
	}
	return info;
}

void CollisionHandler::handlePowerUpWindow(std::vector<std::shared_ptr<PowerUp>>& powers, sf::RectangleShape& window)
{
	for (auto it = powers.begin(); it != powers.end();) {
		auto pos = (*it)->getSprite().getPosition();
		auto startWindow = window.getPosition();
		auto sizeWindow = window.getSize();
		sf::Vector2f size((*it)->getSprite().getGlobalBounds().width, (*it)->getSprite().getGlobalBounds().height);
		if (pos.y + size.y > sizeWindow.y + startWindow.y) {
			it = powers.erase(it);	// remove powerup if out of boarder
			return;
		}
		++it;
	}
}

PowerType CollisionHandler::handlePowerPlatform(std::vector<std::shared_ptr<PowerUp>>& powers, const sf::FloatRect& platform_rect)
{
	PowerType type = PowerType::EMPTY;
	for (auto it = powers.begin(); it != powers.end();) {
		if (platform_rect.intersects((**it).getSprite().getGlobalBounds())) {
			type = (*it)->getType();
			it = powers.erase(it); // Remove brick after collision
			return type;
		}
		else {
			++it;
		}
	}
	return type;
}

bool CollisionHandler::handlePlatformWindow(const sf::FloatRect& platform_rect, const sf::RectangleShape& window_shape)
{
	auto platform_pos = platform_rect.getPosition().x;
	auto platform_size = platform_rect.getSize();

	auto startWindow = window_shape.getPosition();
	auto sizeWindow = window_shape.getSize();

	if (platform_pos < startWindow.x + 3) {
		return true;
	}
	else if (platform_pos + platform_size.x > startWindow.x + sizeWindow.x - 3) {
		return true;
	}
	return false;
}

bool CollisionHandler::keepBallInBoarder(std::shared_ptr<Ball>& ball , const sf::RectangleShape& rectangle)
{
	auto ballShape = ball->getSprite();
	auto velocity = ball->getVelocity();
	auto pos = ballShape.getPosition();
	sf::Vector2f size(ballShape.getGlobalBounds().width, ballShape.getGlobalBounds().height);

	auto startWindow = rectangle.getPosition();
	auto sizeWindow = rectangle.getSize();

	if (pos.x < startWindow.x) {
		velocity.x = std::abs(velocity.x);
	}
	else if (pos.x + size.x > sizeWindow.x + startWindow.x) {
		velocity.x = -std::abs(velocity.x);
	}

	if (pos.y < startWindow.y) {
		velocity.y = std::abs(velocity.y);
	}
	else if (pos.y + size.y > sizeWindow.y + startWindow.y) {
		return true; // Exit the function after deleting the ball
	}

	ball->setVelocity(velocity);
	return false;
}

void CollisionHandler::keepPlatformInBoarder(sf::RectangleShape& platform, const sf::RectangleShape& rectangle)
{
	auto pos = platform.getPosition();
	sf::Vector2f size(platform.getGlobalBounds().width, platform.getGlobalBounds().height);

	auto startWindow = rectangle.getPosition();
	auto sizeWindow = rectangle.getSize();

	if (pos.x < startWindow.x + 20) {
		platform.move(4.0f, 0.0f);
	}
	else if (pos.x + size.x > startWindow.x + sizeWindow.x - 20) {
		platform.move(-4.0f, 0.0f);
	}
}

void CollisionHandler::resolveBallBrick(Ball& ball, Brick& brick) {

	sf::FloatRect ballBounds = ball.getSprite().getGlobalBounds();
	sf::FloatRect brickBounds = brick.getSprite().getGlobalBounds();

	float ballLeft = ballBounds.left;
	float ballRight = ballBounds.left + ballBounds.width;
	float ballTop = ballBounds.top;
	float ballBottom = ballBounds.top + ballBounds.height;

	float brickLeft = brickBounds.left;
	float brickRight = brickBounds.left + brickBounds.width;
	float brickTop = brickBounds.top;
	float brickBottom = brickBounds.top + brickBounds.height;

	// Determine the side of the collision
	bool fromLeft = (ballRight > brickLeft) && (ballLeft < brickLeft) && (ballBottom > brickTop) && (ballTop < brickBottom);
	bool fromRight = (ballLeft < brickRight) && (ballRight > brickRight) && (ballBottom > brickTop) && (ballTop < brickBottom);
	bool fromTop = (ballBottom > brickTop) && (ballTop < brickTop) && (ballRight > brickLeft) && (ballLeft < brickRight);
	bool fromBottom = (ballTop < brickBottom) && (ballBottom > brickBottom) && (ballRight > brickLeft) && (ballLeft < brickRight);

	if (fromLeft && fromBottom) {
		float y_len = brickBottom - ballTop;
		float x_len = ballRight - brickLeft;
		if (y_len > x_len)
			fromBottom = false;
		else
			fromLeft = false;
	}

	if (fromRight && fromBottom) {
		float y_len = brickBottom - ballTop;
		float x_len = brickRight - ballLeft;
		if (y_len > x_len)
			fromBottom = false;
		else
			fromRight = false;
	}

	if (fromLeft && fromTop) {
		float y_len = ballBottom - brickTop;
		float x_len = ballRight - brickLeft;
		if (y_len > x_len)
			fromTop = false;
		else
			fromLeft = false;
	}

	if (fromRight && fromTop) {
		float y_len = ballBottom - brickTop;
		float x_len = brickRight - ballLeft;
		if (y_len > x_len)
			fromTop = false;
		else
			fromRight = false;
	}

	sf::Vector2f newVelocity = ball.getVelocity();

	if (fromLeft || fromRight) {
		newVelocity.x = -newVelocity.x; // Reverse horizontal direction
	}

	if (fromTop || fromBottom) {
		newVelocity.y = -newVelocity.y; // Reverse vertical direction
	}

	ball.setVelocity(newVelocity);
}