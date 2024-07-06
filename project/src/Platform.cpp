#include "Platform.h"

Platform::Platform(sf::Sprite& sprite)
    : m_sticky(false), m_sprite(&sprite), m_short(false), m_long(false)
{
    // Platfrom Sprite
    m_sprite->setPosition(570.f, 800.f);
    m_sprite->setScale(2.3f,2.f);
}

void Platform::update(float dt)
{
 
}

void Platform::draw(sf::RenderWindow& window) const
{
    for (auto& ball : m_stickyBalls) {
        ball->draw(window);
    }
    window.draw(*m_sprite);
}

void Platform::move(float x, float y)
{
    m_sprite->move(x, y);
    for (auto& ball : m_stickyBalls) {
        ball->move(x, y);
    }
}

void Platform::reset(sf::Sprite& ballSprite, sf::Sprite& platformSprite, sf::RectangleShape& window)
{
    float centerWindow = (window.getPosition().x + (window.getGlobalBounds().width / 2));
    float offsetPlatform = platformSprite.getGlobalBounds().width / 2;
    float windowBottom = window.getPosition().y + window.getGlobalBounds().height;

    setSticky(false);
    m_long = false;
    m_short = false;
    m_sprite = &platformSprite;
    m_sprite->setPosition(centerWindow - offsetPlatform, windowBottom - 60.f);
    initStickyBall(ballSprite);
}


sf::FloatRect Platform::getRect() const
{
    return m_sprite->getGlobalBounds();
}

bool Platform::isSticky() const
{
    return m_sticky;
}

bool Platform::isShort() const
{
    return m_short;
}

bool Platform::isLong() const
{
    return m_long;
}

void Platform::makeShort(sf::Sprite& shortSprite, sf::Sprite& midSprite)
{
    auto currentWidth = m_sprite->getGlobalBounds().width;

    if (m_long) {
        m_long = false;
        this->setSprite(midSprite);
    }
    else {
        m_short = true;
        this->setSprite(shortSprite);
    }

    auto offsetX = currentWidth - m_sprite->getGlobalBounds().width;
    offsetX /= 2;
    m_sprite->move(offsetX, 0.f);
}

void Platform::makeLong(const sf::RectangleShape& window, sf::Sprite& longSprite, sf::Sprite& midSprite)
{
    float currentWidth = m_sprite->getGlobalBounds().width;
    float windowLeftPos = window.getPosition().x;
    float windowRightPos = windowLeftPos + window.getGlobalBounds().width;

    if (m_short) {
        m_short = false;
        this->setSprite(midSprite);
    }
    else {
        m_long = true;
        this->setSprite(longSprite);
    }

    auto offsetX = m_sprite->getGlobalBounds().width - currentWidth;
    offsetX /= 2;
    m_sprite->move(-offsetX, 0.f);

    if (windowLeftPos > m_sprite->getPosition().x) {
        m_sprite->move(offsetX, 0.f);
    }
    else if (windowRightPos < m_sprite->getPosition().x + m_sprite->getGlobalBounds().width) {
        m_sprite->move(-offsetX, 0.f);
    }
}

void Platform::setSprite(sf::Sprite& sprite)
{
    auto pos = m_sprite->getPosition();
    auto scale = m_sprite->getScale();
    sprite.setPosition(pos);
    sprite.setScale(scale);
    m_sprite = &sprite;
}

void Platform::setSticky(const bool state)
{
    m_sticky = state;
}

void Platform::splitSticky(sf::Sprite& sprite)
{
    if (getStickyBallsNum() != 1)
        return;

    float x_pos = m_sprite->getGlobalBounds().getPosition().x;
    float y_pos = m_sprite->getGlobalBounds().getPosition().y;

    m_stickyBalls.push_back(std::make_shared<Ball>(sf::Vector2f(x_pos + 35.f, y_pos - 20.f), sf::Vector2f(0.f, 0.f), sprite));
    m_stickyBalls.push_back(std::make_shared<Ball>(sf::Vector2f(x_pos + 95.f, y_pos - 20.f), sf::Vector2f(0.f, 0.f), sprite));
}

void Platform::addSticky(std::shared_ptr<Ball>& ball)
{
    m_stickyBalls.push_back(ball);
}

int Platform::getStickyBallsNum() const
{
    if (!m_stickyBalls.empty()) {
        return (int)m_stickyBalls.size();
    }
    return 0;
}

void Platform::initStickyBall(sf::Sprite& sprite)
{
    float x_pos = m_sprite->getGlobalBounds().getPosition().x;
    float y_pos = m_sprite->getGlobalBounds().getPosition().y;

    m_stickyBalls.clear();
    m_stickyBalls.push_back(std::make_shared<Ball>(sf::Vector2f(x_pos + 65.f, y_pos - 20.f), sf::Vector2f(0.f, 0.f), sprite));
}

 void* Platform::getListOfStickyBalls()
{
     return &m_stickyBalls;
}