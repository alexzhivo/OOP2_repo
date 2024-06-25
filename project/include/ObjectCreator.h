#pragma once

#include <SFML/Graphics.hpp>


class ObjectCreator {
public:
	ObjectCreator();
	sf::Text createTextButton(const std::string& text, const int charSize,
		const char colorChar, const float pos_x, const float pos_y);
	
	sf::RectangleShape createRectangle(const float width, const float height,
		const char colorChar, const float pos_x, const float pos_y);
private:
	sf::Color getColor(const char colorChar);

	sf::Font m_font;
};