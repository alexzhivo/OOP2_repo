#include "Brick.h"

Brick::Brick(int level, float pos_x, float pos_y , float width, float height)
	: m_level(level)
{
	if (level < 1 || level > 3) {
		m_level = 3;	// default brick level is 3
	}

	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setPosition(pos_x, pos_y);
	setColor(m_level);
}

void Brick::update(float dt)
{
	
}

void Brick::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

bool Brick::hit(int power)
{
	m_level -= power;
	if (m_level < 1) {
		return true;	// brick is broken
	}
	setColor(m_level);
	return false;	// if brick is not broken
}

const sf::RectangleShape& Brick::getShape() const
{
	return m_shape;
}

void Brick::setColor(int level)
{
	switch (level) {
	case 1:
		m_shape.setFillColor(sf::Color::Cyan);
		return;
	case 2:
		m_shape.setFillColor(sf::Color::Yellow);
		return;
	case 3:
		m_shape.setFillColor(sf::Color::Magenta);
		return;
	}
}