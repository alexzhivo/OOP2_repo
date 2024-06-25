#include "ObjectCreator.h"

ObjectCreator::ObjectCreator() 
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // >> FONT LOADING ERROR <<
    }
}

sf::Text ObjectCreator::createTextButton(const std::string& text, const int charSize,
    const char colorChar, const float pos_x , const float pos_y)
{
    sf::Text newText;
    newText.setFont(m_font);
    newText.setString(text);
    newText.setCharacterSize(charSize);
    newText.setFillColor(getColor(colorChar));
    newText.setPosition(pos_x, pos_y);

    return newText;
}

sf::RectangleShape ObjectCreator::createRectangle(const float width, const float height,
    const char colorChar, const float pos_x, const float pos_y)
{
    sf::RectangleShape newShape;
    newShape.setSize(sf::Vector2f(width, height));
    newShape.setFillColor(getColor(colorChar));
    newShape.setPosition(sf::Vector2f(pos_x, pos_y));

    return newShape;
}

sf::Color ObjectCreator::getColor(const char colorChar)
{
    switch (colorChar) {

    case 'W':
        // default color (white)
        break;
    case 'B':
        return sf::Color::Black;
    case 'G':
        return sf::Color(100, 100, 100);
    case 'C':
        return sf::Color(200, 200, 200);
    case 'M':
        return sf::Color(0, 0, 0, 180);
    default :
        break;
    }

    return sf::Color::White;
}