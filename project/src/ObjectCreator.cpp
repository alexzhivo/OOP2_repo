#include "ObjectCreator.h"

ObjectCreator::ObjectCreator() 
{
    // LOAD FONTS
    if (!m_font.loadFromFile("arcadefont.ttf"))
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    // load sprites
    loadTexture("wallpaper");
    loadTexture("game_title");
    loadTexture("help_text");
    loadTexture("platform_long");
    loadTexture("platform_sm");
    loadTexture("platform");
    loadTexture("bar_grey");
    loadTexture("brick_blue");
    loadTexture("brick_green");
    loadTexture("brick_red");
    loadTexture("heart_blue");
    loadTexture("heart_red");
    loadTexture("ball");
    loadTexture("big_ball");
    loadTexture("power_lowscore");
    loadTexture("power_upscore");
    loadTexture("power_split");
    loadTexture("power_sticky");
    loadTexture("power_add_life");
    loadTexture("power_dec_life");
    loadTexture("power_long");
    loadTexture("power_short");
    loadTexture("power_inc_ball");

    // load colors
    m_colors["white"] = sf::Color::White;
    m_colors["black"] = sf::Color::Black;
    m_colors["red"] = sf::Color::Red;
    m_colors["green"] = sf::Color::Green;
    m_colors["dark_grey"] = sf::Color(100, 100, 100);
    m_colors["light_grey"] = sf::Color(200, 200, 200);
    m_colors["black_t"] = sf::Color(0, 0, 0, 180);
    m_colors["dark_blue"] = sf::Color(16, 44, 87);
}

sf::Text ObjectCreator::createText(const std::string& text, const int charSize,
    const std::string& colorName, const float pos_x , const float pos_y)
{
    sf::Text newText;
    newText.setFont(m_font);
    newText.setString(text);
    newText.setCharacterSize(charSize);
    newText.setFillColor(getColor(colorName));
    newText.setPosition(pos_x, pos_y);

    return newText;
}

sf::RectangleShape ObjectCreator::createRectangle(const float width, const float height,
    const std::string& colorName, const float pos_x, const float pos_y)
{
    sf::RectangleShape newShape;
    newShape.setSize(sf::Vector2f(width, height));
    newShape.setFillColor(getColor(colorName));
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
        static sf::Sprite defaultSprite; // Return a default if not found
        return defaultSprite;
    }
}

sf::Texture& ObjectCreator::getTexture(const std::string& name)
{
    auto it = m_textures.find(name);
    if (it != m_textures.end()) {
        return it->second;
    }
    else {
        std::cerr << "Texture not found: " << name << std::endl;
        static sf::Texture defaultTexture; // Return a default if not found
        return defaultTexture;
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


sf::Color& ObjectCreator::getColor(const std::string& name)
{
    auto it = m_colors.find(name);
    if (it != m_colors.end()) {
        return it->second;
    }
    else {
        std::cerr << "Color '" << name << "' not found in the map." << std::endl;
    }
    return m_colors["white"];
}