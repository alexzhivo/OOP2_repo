#include "ObjectCreator.h"

ObjectCreator::ObjectCreator() 
{
    // LOAD FONTS
    if (!m_font.loadFromFile("arcadefont.ttf"))
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    // LOAD SPRITES
    loadTexture("platform_long");
    loadTexture("platform_sm");
    loadTexture("platform_mid");
    loadTexture("bar_grey");
    loadTexture("brick_blue");
    loadTexture("brick_green");
    loadTexture("brick_red");
    loadTexture("heart_blue");
    loadTexture("heart_red");
    loadTexture("ball");
    loadTexture("wallpaper");
    loadTexture("power_lowscore");
    loadTexture("power_upscore");

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

sf::Sprite& ObjectCreator::getSprite(const std::string& name)
{
    auto it = m_sprites.find(name);
    if (it != m_sprites.end()) {
        return it->second;
    }
    else {
        std::cerr << "Sprite not found: " << name << std::endl;
        static sf::Sprite defaultSprite; // Return a default sprite if not found
        return defaultSprite;
    }
}

bool ObjectCreator::loadTexture(const std::string& name)
{
    sf::Texture texture;
    sf::Sprite sprite;

    if (!texture.loadFromFile(name + ".png")) {
        std::cerr << "Error loading texture file: " << name + ".png" << std::endl;
        return false;
    }
    m_textures[name] = texture;

    sprite.setTexture(m_textures[name]);
    m_sprites[name] = sprite;

    return true;
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
    case 'D':
        return sf::Color(16, 44, 87);
    default :
        break;
    }

    return sf::Color::White;
}