#include "Brick.h"

Brick::Brick(int level, float pos_x, float pos_y , float width, float height, sf::Sprite& sprite)
	: m_level(level), m_sprite(sprite)
{
	if (level < 1 || level > 3) {
		m_level = 3;	// default brick level is 3
	}

	m_sprite.setPosition(pos_x, pos_y);
	m_sprite.setScale(2.2f, 2.f);
}

void Brick::update(float dt)
{
	
}

void Brick::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

bool Brick::hit(int power)
{
	m_level -= power;
	if (m_level < 1) {
		return true;	// brick is broken
	}
	return false;	// if brick is not broken
}

const sf::Sprite& Brick::getSprite() const
{
	return m_sprite;
}