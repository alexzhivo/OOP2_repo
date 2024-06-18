#include "FinishWindow.h"

FinishWindow::FinishWindow(sf::RenderWindow& window)
	: Window(window)
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Handle font loading error
    }

    // Set up title
    m_title.setFont(m_font);
    m_title.setString("YOU WIN!");
    m_title.setCharacterSize(100);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(300.f, 200.f);
}

UserChoice FinishWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            choice.isSelected = true;
            choice.nextWindow = WindowState::MENU;
            resetWindow();
        }
    }
    return choice;
}

void FinishWindow::update(float dt)
{

}

void FinishWindow::render()
{
    m_window.draw(m_title);
}

void FinishWindow::resetWindow()
{

}