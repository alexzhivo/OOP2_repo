#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow(sf::RenderWindow& window)
    : Window(window), m_currBackButton(false)
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Handle font loading error
    }

    // Set up title
    m_title.setFont(m_font);
    m_title.setString("LEADERBOARD");
    m_title.setCharacterSize(100);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(300.f, 200.f);

    // Set up subtext
    m_backButton.setFont(m_font);
    m_backButton.setString("<< BACK >>");
    m_backButton.setCharacterSize(20);
    m_backButton.setFillColor(sf::Color(100, 100, 100));
    m_backButton.setPosition(500.f, 700.f);
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