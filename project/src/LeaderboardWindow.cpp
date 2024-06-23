#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    : Window(window,objectCreator), m_currBackButton(false)
{
    m_title = objectCreator->createTextButton("LEADERBOARD", 100, 'W', 300.f, 200.f);
    m_backButton = objectCreator->createTextButton("<< BACK >>", 20, 'G', 500.f, 700.f);
}

UserChoice LeaderboardWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter && m_currBackButton) {
            choice.isSelected = true;
            choice.nextWindow = WindowState::MENU;
            resetWindow();
        }
        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up) {
            if (m_currBackButton)
                m_currBackButton = false;
            else
                m_currBackButton = true;
        }
    }
    return choice;
}

void LeaderboardWindow::update(float dt)
{
    updateHover();
}

void LeaderboardWindow::render()
{
    m_window.draw(m_title);
    m_window.draw(m_backButton);
}

void LeaderboardWindow::resetWindow()
{
    m_currBackButton = false;
}

void LeaderboardWindow::updateHover()
{
    if (m_currBackButton) {
        m_backButton.setFillColor(sf::Color::White);
    }
    else {
        m_backButton.setFillColor(sf::Color(100, 100, 100));
    }
}