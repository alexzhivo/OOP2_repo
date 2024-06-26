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
    // title
    m_title = m_objectCreator->createTextButton("GAME MENU",100,'W',345.f,100.f);
    // buttons
    m_buttons.push_back(m_objectCreator->createTextButton("PLAY GAME", 50, 'W', 510.f, 350.f));
    m_buttons.push_back(m_objectCreator->createTextButton("LEADERBOARD", 50, 'W', 465.f, 450.f));
    m_buttons.push_back(m_objectCreator->createTextButton("HELP", 50, 'W', 580.f, 550.f));
    m_buttons.push_back(m_objectCreator->createTextButton("SETTINGS", 50, 'W', 520.f, 650.f));
    m_buttons.push_back(m_objectCreator->createTextButton("EXIT", 50, 'W', 590.f, 750.f));
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
    for (const auto& button : m_buttons)
        m_window.draw(button);
}

void MenuWindow::resetWindow()
{
    m_currHoverButton = MenuButton::NONE;
    resetAllButtons();
}

void MenuWindow::updateHover()
{
    if (m_currHoverButton != MenuButton::NONE) {
        resetAllButtons();
        m_buttons[(int)m_currHoverButton].setFillColor(sf::Color::Blue);
    }
}

void MenuWindow::resetAllButtons()
{
    for (auto& button : m_buttons)
        button.setFillColor(sf::Color::White);
}