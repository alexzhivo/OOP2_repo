#include "HelpWindow.h"

HelpWindow::HelpWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager)
    : Window(window,objectCreator,soundManager), m_currBackButton(false)
{
    m_title = objectCreator->createTextButton("Instructions:", 60, 'W', 200.f, 200.f);
    m_backButton = objectCreator->createTextButton("<< BACK >>",20,'G',550.f,730.f);
}

UserChoice HelpWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter && m_currBackButton) {
            m_soundManager->playSound("select", false);
            choice.isSelected = true;
            choice.nextWindow = WindowState::MENU;
            resetWindow();
        }
        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up) {
            m_soundManager->playSound("hover", false);
            if (m_currBackButton)
                m_currBackButton = false;
            else
                m_currBackButton = true;
        }
    }
    return choice;
}

void HelpWindow::update(float dt)
{
    updateHover();
}

void HelpWindow::render()
{
    m_window.draw(m_title);
    m_window.draw(m_backButton);
}

void HelpWindow::resetWindow()
{
    m_currBackButton = false;
}

void HelpWindow::updateHover()
{
    if (m_currBackButton) {
        m_backButton.setFillColor(sf::Color::White);
    }
    else {
        m_backButton.setFillColor(sf::Color(100,100,100));

    }
}