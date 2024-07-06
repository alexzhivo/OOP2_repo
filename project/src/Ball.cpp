#include "Ball.h"

#include <iostream>	// TEST

Ball::Ball(sf::Vector2f position, sf::Vector2f velocity, sf::Sprite& sprite)
	: m_initVelocity(velocity), m_sprite(sprite), m_speed(300.f)
{
	m_sprite.setPosition(position);
	m_sprite.setScale(2.5f, 2.5f);

	setVelocity(m_initVelocity);
}

void Ball::update(float dt)
{
	sf::Vector2f pos = m_sprite.getPosition();
	pos += m_currVelocity * dt;
	m_sprite.setPosition(pos);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Ball::setVelocity(sf::Vector2f velocity)
{
	m_currVelocity = velocity;
	if (velocity.x != 0 && velocity.y != 0) {
		m_lastVelocity = velocity;
	}
}

void Ball::setVelocityZero()
{
	m_currVelocity.x = 0;
	m_currVelocity.y = 0;
}

sf::Vector2f Ball::getVelocity() const
{
	return m_currVelocity;
}

void Ball::restoreVelocity()
{
	setVelocity(m_lastVelocity);
}

const sf::Sprite& Ball::getSprite() const
{
	return m_sprite;
}

float Ball::getSpeed() const
{
	return m_speed;
}

void Ball::move(float offsetX, float offsetY)
{
	m_sprite.move(offsetX, offsetY);
}

void Ball::release(float radians)
{
	sf::Vector2f newVelocity;
	newVelocity.x = std::sin(radians) * m_speed;
	newVelocity.y = m_speed * std::cos(radians);
	newVelocity.y = -newVelocity.y; // Reverse vertical direction

	setVelocity(newVelocity);
}