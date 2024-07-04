#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Ball.h"

#include <iostream>

class Platform {
public:
	Platform(sf::Sprite& sprite);
	void update(float dt);
	void draw(sf::RenderWindow& window) const;

	sf::FloatRect getRect() const;

	void move(float x, float y);
	void reset(sf::Sprite& sprite);

	// sticky feature
	bool isSticky() const;
	void setSticky(const bool state);
	int getStickyBallsNum() const;
	void initStickyBall(sf::Sprite& sprite);
	std::shared_ptr<Ball> releaseBall();

private:
	sf::Sprite& m_sprite;
	bool m_sticky;
	std::list<std::shared_ptr<Ball>> m_stickyBalls;
};