#include "PowerUp.h"

PowerUp::PowerUp(const PowerType& type,const sf::Vector2f& position)
	: m_type(type)
{
	m_shape.setSize(sf::Vector2f(20.f, 20.f));
	m_shape.setPosition(position);
	m_shape.setFillColor(getColorByType(type));
}

void PowerUp::update(float dt)
{
	m_shape.move(0.f,100.f * dt);
}

void PowerUp::draw(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}

sf::RectangleShape& PowerUp::getShape()
{
	return m_shape;
}

sf::Color PowerUp::getColorByType(const PowerType& type) const
{
	switch (type) {
	case PowerType::ADD_PTS:
		return sf::Color::Green;
	case PowerType::DEC_PTS:
		return sf::Color::Red;
	}
	return sf::Color::Green;
}