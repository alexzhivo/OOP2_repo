#include "Platform.h"

Platform::Platform()
{
	// create shape for platform
    m_shape.setPosition(300.f, 800.f);
    m_shape.setSize(sf::Vector2f(150.f, 20.f));
    m_shape.setFillColor(sf::Color::Green);
}

void Platform::update(float dt)
{
    // Handle platform movement based on input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_shape.move(-400.0f * dt, 0.0f); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_shape.move(400.0f * dt, 0.0f); // Move right
    }
}

void Platform::draw(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}

sf::RectangleShape& Platform::getShape()
{
    return m_shape;
}