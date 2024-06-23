#include "MenuWindow.h"

// enum class Button operators
MenuButton& operator++(MenuButton& button) {    // SCROLL DOWN
    auto buttonNum = static_cast<int>(button);
    buttonNum++;
    button = static_cast<MenuButton>(buttonNum);
    if (buttonNum >= NUM_OF_BUTTONS)
        button = static_cast<MenuButton>(0);
    return button;
}

MenuButton& operator--(MenuButton& button) {    // SCROLL UP
    auto buttonNum = static_cast<int>(button);
    buttonNum--;
    button = static_cast<MenuButton>(buttonNum);
    if (buttonNum < 0)
        button = static_cast<MenuButton>(NUM_OF_BUTTONS - 1);
    return button;
}

// MenuWindow Class
MenuWindow::MenuWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
	: Window(window,objectCreator), m_currHoverButton(MenuButton::NONE)
{
    m_title = m_objectCreator->createTextButton("GAME MENU",100,'W',350.f,200.f);
    m_playButton = m_objectCreator->createTextButton("PLAY GAME", 50, 'W', 350.f, 400.f);
    m_leaderboardButton = m_objectCreator->createTextButton("LEADERBOARD", 50, 'W', 350.f, 500.f);
    m_helpButton = m_objectCreator->createTextButton("HELP", 50, 'W', 350.f, 600.f);
    m_settingsButton = m_objectCreator->createTextButton("SETTINGS", 50, 'W', 350.f, 700.f);
    m_exitButton = m_objectCreator->createTextButton("EXIT", 50, 'W', 350.f, 800.f);
}

UserChoice MenuWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        auto currHoverButtonNum = static_cast<int>(m_currHoverButton);
        if (event.key.code == sf::Keyboard::Escape) { 
            choice.isSelected = true;
            choice.nextWindow = WindowState::EXIT;
        }
        else if (event.key.code == sf::Keyboard::Up) {
            if (currHoverButtonNum == NUM_OF_BUTTONS)
                m_currHoverButton = MenuButton::PLAY;
            else
                --m_currHoverButton;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            if (currHoverButtonNum == NUM_OF_BUTTONS)
                m_currHoverButton = MenuButton::PLAY;
            else
                ++m_currHoverButton;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (currHoverButtonNum != NUM_OF_BUTTONS) {
                choice.isSelected = true;
                if (currHoverButtonNum == (int)MenuButton::EXIT)
                    choice.nextWindow = WindowState::EXIT;
                else 
                    choice.nextWindow = static_cast<WindowState>(currHoverButtonNum + 2);
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
    m_currHoverButton = MenuButton::NONE;
}

void MenuWindow::updateHover()
{
    switch (m_currHoverButton) {
    case MenuButton::PLAY:
        resetAllButtons();
        m_playButton.setFillColor(sf::Color::Blue);
        break;
    case MenuButton::LEADERBOARD:
        resetAllButtons();
        m_leaderboardButton.setFillColor(sf::Color::Blue);
        break;
    case MenuButton::HELP:
        resetAllButtons();
        m_helpButton.setFillColor(sf::Color::Blue);
        break;
    case MenuButton::SETTINGS:
        resetAllButtons();
        m_settingsButton.setFillColor(sf::Color::Blue);
        break;
    case MenuButton::EXIT:
        resetAllButtons();
        m_exitButton.setFillColor(sf::Color::Blue);
        break;
    case MenuButton::NONE:
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