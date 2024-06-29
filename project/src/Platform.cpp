#include "Platform.h"

Platform::Platform()
    : m_sticky(false)
{
	// create shape for platform
    m_shape.setPosition(570.f, 800.f);
    m_shape.setSize(sf::Vector2f(150.f, 20.f));
    m_shape.setFillColor(sf::Color::Green);
}

void Platform::update(float dt)
{
    // Handle platform movement based on input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_shape.move(-600.0f * dt, 0.0f); // Move left
        for (auto& ball : m_stickyBalls)
            ball->move(-600.f * dt, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_shape.move(600.0f * dt, 0.0f); // Move right
        for (auto& ball : m_stickyBalls)
            ball->move(600.f * dt, 0.0f);
    }
}

void Platform::draw(sf::RenderWindow& window) const
{
    for (auto& ball : m_stickyBalls) {
        ball->draw(window);
    }
	window.draw(m_shape);
}

void Platform::reset()
{
    m_shape.setPosition(570.f, 800.f);
    setSticky(false);
    initStickyBall();
}

sf::RectangleShape& Platform::getShape()
{
    return m_shape;
}

bool Platform::isSticky() const
{
    return m_sticky;
}

void Platform::setSticky(const bool state)
{
    m_sticky = state;
}

int Platform::getStickyBallsNum() const
{
    return (int)m_stickyBalls.size();
}

void Platform::initStickyBall()
{
    m_stickyBalls.clear();
    m_stickyBalls.push_back(std::make_shared<Ball>(sf::Vector2f(635.f,770.f), sf::Vector2f(0.f, 0.f)));
}

std::shared_ptr<Ball> Platform::releaseBall() 
{
    if (!m_stickyBalls.empty()) {
        auto it = m_stickyBalls.begin();
        std::shared_ptr<Ball> ball = *it;
        m_stickyBalls.erase(it);
        return ball;
    }
    return nullptr;
}