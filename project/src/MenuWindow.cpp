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
MenuWindow::MenuWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager)
	: Window(window,objectCreator,soundManager), m_currHoverButton(MenuButton::NONE)
{
    // title
    m_title = m_objectCreator->createText("GAME MENU",90,"white",230.f,150.f);
    // buttons
    m_buttons.push_back(m_objectCreator->createText("PLAY GAME", 40, "white", 300.f, 350.f));
    m_buttons.push_back(m_objectCreator->createText("LEADERBOARD", 40, "white", 300.f, 450.f));
    m_buttons.push_back(m_objectCreator->createText("HELP", 40, "white", 300.f, 550.f));
    m_buttons.push_back(m_objectCreator->createText("SETTINGS", 40, "white", 300.f, 650.f));
    m_buttons.push_back(m_objectCreator->createText("EXIT", 40, "white", 300.f, 750.f));
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
            m_soundManager->playSound("hover", false);
            if (currHoverButtonNum == NUM_OF_BUTTONS)
                m_currHoverButton = MenuButton::PLAY;
            else
                --m_currHoverButton;
        }
        else if (event.key.code == sf::Keyboard::Down) {
            m_soundManager->playSound("hover", false);
            if (currHoverButtonNum == NUM_OF_BUTTONS)
                m_currHoverButton = MenuButton::PLAY;
            else
                ++m_currHoverButton;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (currHoverButtonNum != NUM_OF_BUTTONS) {
                m_soundManager->playSound("select", false);
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