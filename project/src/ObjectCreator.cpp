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
    default :
        break;
    }

    return sf::Color::White;
}