#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Ball.h"

#include <iostream>

class Platform {
public:
	Platform();
	void update(float dt);
	void draw(sf::RenderWindow& window) const;

	sf::RectangleShape& getShape();
	void reset();

	// sticky feature
	bool isSticky() const;
	void setSticky(const bool state);
	int getStickyBallsNum() const;
	void initStickyBall();
	std::shared_ptr<Ball> releaseBall();

private:
	sf::RectangleShape m_shape;
	std::list<std::shared_ptr<Ball>> m_stickyBalls;
	bool m_sticky;
};