#include "MenuWindow.h"

// enum class Button operators
Button& operator++(Button& button) {
    button = static_cast<Button>(static_cast<int>(button) + 1);
    if (static_cast<int>(button) > 4) {
        button = static_cast<Button>(0);
    }
    return button;
}

Button& operator--(Button& button) {
    button = static_cast<Button>(static_cast<int>(button) - 1);
    if (static_cast<int>(button) < 0) {
        button = static_cast<Button>(static_cast<int>(Button::EXIT));
    }
    return button;
}

// MenuWindow Class
MenuWindow::MenuWindow(sf::RenderWindow& window)
	: Window(window), m_currHoverButton(Button::NONE)
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Handle font loading error
    }
    m_title.setFont(m_font);
    m_playButton.setFont(m_font);
    m_leaderboardButton.setFont(m_font);
    m_helpButton.setFont(m_font);
    m_settingsButton.setFont(m_font);
    m_exitButton.setFont(m_font);

    // Set up title
    m_title.setString("GAME MENU");
    m_title.setCharacterSize(100);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(350.f, 200.f);

    // Set up Buttons
    m_playButton.setString("PLAY GAME");
    m_playButton.setCharacterSize(50);
    m_playButton.setFillColor(sf::Color::White);
    m_playButton.setPosition(350.f, 400.f);

    m_leaderboardButton.setString("LEADERBOARD");
    m_leaderboardButton.setCharacterSize(50);
    m_leaderboardButton.setFillColor(sf::Color::White);
    m_leaderboardButton.setPosition(350.f, 500.f);

    m_helpButton.setString("HELP");
    m_helpButton.setCharacterSize(50);
    m_helpButton.setFillColor(sf::Color::White);
    m_helpButton.setPosition(350.f, 600.f);

    m_settingsButton.setString("SETTINGS");
    m_settingsButton.setCharacterSize(50);
    m_settingsButton.setFillColor(sf::Color::White);
    m_settingsButton.setPosition(350.f, 700.f);

    m_exitButton.setString("EXIT");
    m_exitButton.setCharacterSize(50);
    m_exitButton.setFillColor(sf::Color::White);
    m_exitButton.setPosition(350.f, 800.f);
}

UserChoice MenuWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) { 
            choice.isSelected = true;
            choice.nextWindow = WindowState::EXIT;
        }
        else if (event.key.code == sf::Keyboard::Up) {
            if ((int)m_currHoverButton == 5)
                m_currHoverButton = Button::PLAY;
            else
                --m_currHoverButton;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            if ((int)m_currHoverButton == 5)
                m_currHoverButton = Button::PLAY;
            else
                ++m_currHoverButton;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if ((int)m_currHoverButton != 5) {
                choice.isSelected = true;
                choice.nextWindow = static_cast<WindowState>((int)m_currHoverButton + 2);
                resetWindow();
            }
        }
    }
    return choice;
}

void MenuWindow::update(float dt)
{
    updateHover();
}

void MenuWindow::render()
{
    m_window.draw(m_title);
    m_window.draw(m_playButton);
    m_window.draw(m_leaderboardButton);
    m_window.draw(m_helpButton);
    m_window.draw(m_settingsButton);
    m_window.draw(m_exitButton);
}

void MenuWindow::resetWindow()
{
    m_currHoverButton = Button::NONE;
}

void MenuWindow::updateHover()
{
    switch (m_currHoverButton) {
    case Button::PLAY:
        resetAllButtons();
        m_playButton.setFillColor(sf::Color::Blue);
        break;
    case Button::LEADERBOARD:
        resetAllButtons();
        m_leaderboardButton.setFillColor(sf::Color::Blue);
        break;
    case Button::HELP:
        resetAllButtons();
        m_helpButton.setFillColor(sf::Color::Blue);
        break;
    case Button::SETTINGS:
        resetAllButtons();
        m_settingsButton.setFillColor(sf::Color::Blue);
        break;
    case Button::EXIT:
        resetAllButtons();
        m_exitButton.setFillColor(sf::Color::Blue);
        break;
    case Button::NONE:
        resetAllButtons();
        break;
    }
}

void MenuWindow::resetAllButtons()
{
    m_playButton.setFillColor(sf::Color::White);
    m_leaderboardButton.setFillColor(sf::Color::White);
    m_helpButton.setFillColor(sf::Color::White);
    m_settingsButton.setFillColor(sf::Color::White);
    m_exitButton.setFillColor(sf::Color::White);
}