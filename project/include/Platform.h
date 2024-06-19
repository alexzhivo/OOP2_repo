#pragma once

#include <SFML/Graphics.hpp>

class Platform {
public:
	Platform();
	void update(float dt);
	void draw(sf::RenderWindow& window) const;

private:
	sf::RectangleShape m_shape;
};