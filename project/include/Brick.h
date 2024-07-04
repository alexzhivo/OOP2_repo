#pragma once

#include <SFML/Graphics.hpp>

class Brick {
public:
	Brick(int level , float pos_x, float pos_y, float width, float height, sf::Sprite& sprite);
	void update(float dt);
	void draw(sf::RenderWindow& window);

	bool hit(int power);		// when brick is hit
	const sf::Sprite& getSprite() const;

private:
	sf::Sprite m_sprite;
	int m_level;
};