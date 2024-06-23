#pragma once

#include <SFML/Graphics.hpp>

class Platform {
public:
	Platform();
	void update(float dt);
	void draw(sf::RenderWindow& window) const;

	sf::RectangleShape& getShape();

private:
	sf::RectangleShape m_shape;
};