#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball(sf::Vector2f position, sf::Vector2f velocity);

	void update(float dt);
	void draw(sf::RenderWindow& window);
	void setVelocity(sf::Vector2f velocity);
	void setVelocityZero();
	sf::Vector2f getVelocity() const;
	void restoreVelocity();
	const sf::CircleShape& getShape() const;
	float getSpeed() const;

	void move(float offsetX, float offsetY);

private:
	sf::CircleShape m_shape;
	sf::Vector2f m_initVelocity;
	sf::Vector2f m_lastVelocity;
	sf::Vector2f m_currVelocity;
	float m_speed = 400.f;
};