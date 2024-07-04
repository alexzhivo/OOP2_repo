#include "PowerUp.h"

PowerUp::PowerUp(const PowerType& type,const sf::Vector2f& position, sf::Sprite& sprite)
	: m_type(type), m_sprite(sprite)
{
	m_sprite.setPosition(position);
	m_sprite.setScale(2.f, 2.f);
}

void PowerUp::update(float dt)
{
	m_sprite.move(0.f,100.f * dt);
}

void PowerUp::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

const PowerType PowerUp::getType() const
{
	return m_type;
}

const sf::Sprite& PowerUp::getSprite() const
{
	return m_sprite;
}