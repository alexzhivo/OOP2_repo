#include "StartWindow.h"

StartWindow::StartWindow(sf::RenderWindow& window)
    : Window(window)
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Handle font loading error
    }

    // Set up title
    m_title.setFont(m_font);
    m_title.setString("BRICKBUSTER");
    m_title.setCharacterSize(100);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(300.f, 200.f);

    // Set up subtext
    m_subtext.setFont(m_font);
    m_subtext.setString("<< Press SPACE To Start >>");
    m_subtext.setCharacterSize(20);
    m_subtext.setFillColor(sf::Color::White);
    m_subtext.setPosition(500.f, 700.f);
}

UserChoice StartWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            choice.isSelected = true;
            choice.nextWindow = GameWindow::MENU;
        }
    }
    return choice;
}

void StartWindow::update()
{

}

void StartWindow::render()
{
	m_window.draw(m_title);
    m_window.draw(m_subtext);
}