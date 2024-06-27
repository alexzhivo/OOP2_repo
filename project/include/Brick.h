#pragma once

#include <SFML/Graphics.hpp>

class Brick {
public:
	Brick(int level , float pos_x, float pos_y, float width, float height);
	void update(float dt);
	void draw(sf::RenderWindow& window);
	bool hit(int power);		// when brick is hit
	const sf::RectangleShape& getShape() const;

private:
	void setColor(int level);	// change brick color

	sf::RectangleShape m_shape;
	int m_level;
};