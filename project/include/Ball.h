#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball(sf::Vector2f position, sf::Vector2f velocity, sf::Sprite& sprite);

	void update(float dt);
	void draw(sf::RenderWindow& window);
	void move(float offsetX, float offsetY);

	const sf::Sprite& getSprite() const;

	void setVelocity(sf::Vector2f velocity);
	void setVelocityZero();
	sf::Vector2f getVelocity() const;
	void restoreVelocity();
	float getSpeed() const;


	void release(float radians);

private:
	sf::Sprite m_sprite;

	sf::Vector2f m_initVelocity;
	sf::Vector2f m_lastVelocity;
	sf::Vector2f m_currVelocity;
	float m_speed;
};