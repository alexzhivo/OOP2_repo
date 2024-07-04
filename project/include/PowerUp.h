#pragma once

#include <SFML/Graphics.hpp>

enum class PowerType {
	ADD_PTS,
	DEC_PTS,
	EMPTY
};

class PowerUp {
public:
	PowerUp(const PowerType& type, const sf::Vector2f& position, sf::Sprite& sprite);
	void update(float dt);
	void draw(sf::RenderWindow& window) const;

	const sf::Sprite& getSprite() const;
	const PowerType getType() const;

private:
	PowerType m_type;
	sf::Sprite m_sprite;
};