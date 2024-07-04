#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class ObjectCreator {
public:
	ObjectCreator();
	
	sf::Text createTextButton(const std::string& text, const int charSize,
		const char colorChar, const float pos_x, const float pos_y);
	
	sf::RectangleShape createRectangle(const float width, const float height,
		const char colorChar, const float pos_x, const float pos_y);

	// SPRITES

	sf::Sprite& getSprite(const std::string& name);

private:
	bool loadTexture(const std::string& name);
	sf::Color getColor(const char colorChar);

	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Sprite> m_sprites;

	sf::Font m_font;
};