#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball(sf::Vector2f position);

	void update(float dt);
	void draw(sf::RenderWindow& window);
	void setVelocity(sf::Vector2f velocity);
	void restoreVelocity();

private:
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	sf::Vector2f m_currVelocity;

	void handleCollision(const sf::Vector2u& windowSize);
};