#include "CollisionHandler.h"

#include <iostream>

void CollisionHandler::handleOutOfBoarder(std::list<std::shared_ptr<Ball>>& balls, sf::RectangleShape& platform, sf::RectangleShape& window)
{
    for (auto& ball : balls) {
		keepBallInBoarder(ball, window);
    }
	keepPlatformInBoarder(platform, window);
}

void CollisionHandler::handleBallPlatform(std::list<std::shared_ptr<Ball>>& balls, sf::RectangleShape& platform)
{
	for (auto& ball : balls) {
		if (ball->getShape().getGlobalBounds().intersects(platform.getGlobalBounds())) {

			float ballCenter = ball->getShape().getPosition().x + ball->getShape().getGlobalBounds().width / 2.0f;
			float platformLeft = platform.getPosition().x;
			float platformRight = platform.getPosition().x + platform.getGlobalBounds().width;
			float platformCenter = platformLeft + platform.getGlobalBounds().width / 2.0f;

			float collisionPoint = ballCenter - platformLeft;
			float platformWidth = platform.getGlobalBounds().width;
			float normalizedCollisionPoint = (collisionPoint / platformWidth) - 0.5f; // Normalize between -0.5 and 0.5

			// Calculate new velocity based on the collision point
			sf::Vector2f newVelocity = ball->getVelocity();

			float angle = normalizedCollisionPoint * 2.0f * 75.0f; // Max bounce angle is 75 degrees
			float radians = angle * 3.14159f / 180.0f;
			float speed = ball->getSpeed();

			newVelocity.x = std::sin(radians) * speed;
			newVelocity.y = speed * std::cos(radians);
			newVelocity.y = -newVelocity.y; // Reverse vertical direction
			
			ball->setVelocity(newVelocity);
			return;
		}
	}
}

void CollisionHandler::handleBallBrick(std::list<std::shared_ptr<Ball>>& balls, std::vector<std::shared_ptr<Brick>>& bricks)
{
	for (auto& ball : balls) {

		for (auto it = bricks.begin(); it != bricks.end();) {
			if (ball->getShape().getGlobalBounds().intersects((*it)->getShape().getGlobalBounds())) {
				resolveBallBrick(*ball, **it);
				if ((*it)->hit(1))
					it = bricks.erase(it); // Remove brick after collision
				return;
			}
			else {
				++it;
			}
		}
	}
}

void CollisionHandler::keepBallInBoarder(std::shared_ptr<Ball>& ball , const sf::RectangleShape& rectangle)
{
	auto ballShape = ball->getShape();
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
		velocity.y = -std::abs(velocity.y);
	}

	ball->setVelocity(velocity);
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

	sf::FloatRect ballBounds = ball.getShape().getGlobalBounds();
	sf::FloatRect brickBounds = brick.getShape().getGlobalBounds();

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

	sf::Vector2f newVelocity = ball.getVelocity();

	if (fromTop || fromBottom) {
		newVelocity.y = -newVelocity.y; // Reverse vertical direction
	}
	else if (fromLeft || fromRight) {
		newVelocity.x = -newVelocity.x; // Reverse horizontal direction
	}

	ball.setVelocity(newVelocity);
}