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
	void reset(sf::Sprite& ballSprite,
			   sf::Sprite& platformSprite,
			   sf::RectangleShape& window);

	// sticky feature
	bool isSticky() const;
	bool isShort() const;
	bool isLong() const;

    void makeShort(sf::Sprite& shortSprite, sf::Sprite& midSprite);
	void makeLong(const sf::RectangleShape& window, sf::Sprite& longSprite, sf::Sprite& midSprite);
	void setSticky(const bool state);
	void setSprite(sf::Sprite& sprite);
	void splitSticky(sf::Sprite& sprite);
	void addSticky(std::shared_ptr<Ball>& ball);
	int getStickyBallsNum() const;
	void initStickyBall(sf::Sprite& sprite);
	void* getListOfStickyBalls();

private:
	sf::Sprite* m_sprite;

	bool m_sticky;
	bool m_short;
	bool m_long;
	std::list<std::shared_ptr<Ball>> m_stickyBalls;
};