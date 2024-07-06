#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>

class ObjectCreator {
public:
	ObjectCreator();
	
	sf::Color& getColor(const std::string& name);

	sf::Text createText(const std::string& text, const int charSize,
		const std::string& colorName, const float pos_x, const float pos_y);
	
	sf::RectangleShape createRectangle(const float width, const float height,
		const std::string& colorName, const float pos_x, const float pos_y);

	// sprites and textures
	sf::Sprite& getSprite(const std::string& name);
	sf::Texture& getTexture(const std::string& name);
private:
	bool loadTexture(const std::string& name);

	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Sprite> m_sprites;
	std::unordered_map<std::string, sf::Color> m_colors;

	sf::Font m_font;
};