#include "CollisionHandler.h"

void CollisionHandler::handleOutOfBoarder(std::list<std::unique_ptr<Ball>>& balls, sf::RectangleShape& window)
{
    for (auto& ball : balls) {
		keepBallInBoarder(ball, window);
    }
}

void CollisionHandler::keepBallInBoarder(std::unique_ptr<Ball>& ball , const sf::RectangleShape& rectangle)
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