#include "Ball.h"

Ball::Ball(sf::Vector2f position)
	: m_velocity(sf::Vector2f(200.f,200.f))
{
	m_shape.setPosition(position);
	m_shape.setRadius(20.f);
	m_shape.setFillColor(sf::Color::Red);
	setVelocity(m_velocity);
}

void Ball::update(float dt)
{
	sf::Vector2f pos = m_shape.getPosition();
	pos += m_currVelocity * dt;
	m_shape.setPosition(pos);

	// handle collision
	handleCollision(sf::Vector2u(1280, 920));	// windowSize
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Ball::setVelocity(sf::Vector2f velocity)
{
	m_currVelocity = velocity;
}

void Ball::restoreVelocity()
{
	setVelocity(m_velocity);
}

void Ball::handleCollision(const sf::Vector2u& windowSize)
{
	sf::Vector2f pos = m_shape.getPosition();
	sf::Vector2f size(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height);
	
	if (pos.x < 0) {
		m_velocity.x = std::abs(m_velocity.x);
	}
	else if (pos.x + size.x > windowSize.x) {
		m_velocity.x = -std::abs(m_velocity.x);
	}

	if (pos.y < 0) {
		m_velocity.y = std::abs(m_velocity.y);
	}
	else if (pos.y + size.y > windowSize.y) {
		m_velocity.y = -std::abs(m_velocity.y);
	}
}