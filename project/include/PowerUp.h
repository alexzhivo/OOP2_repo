#pragma once

#include <SFML/Graphics.hpp>

enum class PowerType {
	ADD_PTS,
	DEC_PTS
};

class PowerUp {
public:
	PowerUp(const PowerType& type, const sf::Vector2f& position);
	void update(float dt);
	void draw(sf::RenderWindow& window) const;

	sf::RectangleShape& getShape();

private:
	PowerType m_type;
	sf::RectangleShape m_shape;

	// inner functions
	sf::Color getColorByType(const PowerType& type) const;
};