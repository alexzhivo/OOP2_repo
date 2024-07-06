#include "Platform.h"

Platform::Platform(sf::Sprite& sprite)
    : m_sticky(false) , m_sprite(sprite)
{
    // Platfrom Sprite
    m_sprite.setPosition(570.f, 800.f);
    m_sprite.setScale(2.3f,2.f);
}

void Platform::update(float dt)
{

}

void Platform::draw(sf::RenderWindow& window) const
{
    for (auto& ball : m_stickyBalls) {
        ball->draw(window);
    }
    window.draw(m_sprite);
}

void Platform::move(float x, float y)
{
    m_sprite.move(x, y);
    for (auto& ball : m_stickyBalls) {
        ball->move(x, y);
    }
}

void Platform::reset(sf::Sprite& sprite)
{
    m_sprite.setPosition(570.f, 800.f);
    setSticky(false);
    initStickyBall(sprite);
}


sf::FloatRect Platform::getRect() const
{
    return m_sprite.getGlobalBounds();
}

bool Platform::isSticky() const
{
    return m_sticky;
}

void Platform::setSticky(const bool state)
{
    m_sticky = state;
}

void Platform::splitSticky(sf::Sprite& sprite)
{
    if (getStickyBallsNum() != 1)
        return;

    float x_pos = m_sprite.getGlobalBounds().getPosition().x;
    float y_pos = m_sprite.getGlobalBounds().getPosition().y;

    m_stickyBalls.push_back(std::make_shared<Ball>(sf::Vector2f(x_pos + 35.f, y_pos - 20.f), sf::Vector2f(0.f, 0.f), sprite));
    m_stickyBalls.push_back(std::make_shared<Ball>(sf::Vector2f(x_pos + 95.f, y_pos - 20.f), sf::Vector2f(0.f, 0.f), sprite));
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
    float x_pos = m_sprite.getGlobalBounds().getPosition().x;
    float y_pos = m_sprite.getGlobalBounds().getPosition().y;

    m_stickyBalls.clear();
    m_stickyBalls.push_back(std::make_shared<Ball>(sf::Vector2f(x_pos + 65.f, y_pos - 20.f), sf::Vector2f(0.f, 0.f), sprite));
}

 void* Platform::getListOfStickyBalls()
{
     return &m_stickyBalls;
}