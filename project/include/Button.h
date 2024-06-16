#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const std::string& text, const sf::Vector2i& position, const sf::Vector2i& size);

    void render(sf::RenderWindow& window) const;

    // bool isMouseOver(const sf::RenderWindow& window) const;
private:
    sf::RectangleShape m_buttonShape;
    sf::Text m_buttonText;
};