#include "Button.h"

Button::Button(const std::string& text, const sf::Vector2i& position, const sf::Vector2i& size)
{
	m_buttonText.setString(text);
	m_buttonText.setPosition((float)position.x, (float)position.y);
	m_buttonText.setCharacterSize(20);
	m_buttonText.setFillColor(sf::Color::White);
	m_buttonShape.setSize(sf::Vector2f((float)size.x, (float)size.y));
}

void Button::render(sf::RenderWindow& window) const {
	window.draw(m_buttonShape);
	window.draw(m_buttonText);
}