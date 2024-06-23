#include "SettingsWindow.h"

// enum class Button operators
Setting& operator++(Setting& setting) {
    setting = static_cast<Setting>(static_cast<int>(setting) + 1);
    if (static_cast<int>(setting) > 2) {
        setting = static_cast<Setting>(0);
    }
    return setting;
}

Setting& operator--(Setting& setting) {
    setting = static_cast<Setting>(static_cast<int>(setting) - 1);
    if (static_cast<int>(setting) < 0) {
        setting = static_cast<Setting>(static_cast<int>(Setting::BACK));
    }
    return setting;
}

SettingsWindow::SettingsWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    : Window(window,objectCreator), m_settingHover(Setting::NONE)
{
    m_title = objectCreator->createTextButton("SETTINGS", 100, 'W', 300.f, 200.f);
    m_gameSoundText = objectCreator->createTextButton("<< Game Sound >>", 30, 'G', 500.f, 400.f);
    m_playerNameText = objectCreator->createTextButton("<< Player Name >>", 30, 'G', 500.f, 500.f);
    m_backButtonText = objectCreator->createTextButton("<< BACK >>", 30, 'G', 500.f, 600.f);
}

UserChoice SettingsWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            if (m_settingHover == Setting::NONE) {
                m_settingHover = Setting::GAMESOUND;
            }
            else {
                if (event.key.code == sf::Keyboard::Up)
                    --m_settingHover;
                else
                    ++m_settingHover;
            }
        }
        else if (event.key.code == sf::Keyboard::Enter && m_settingHover == Setting::BACK) {
                choice.isSelected = true;
                choice.nextWindow = WindowState::MENU;
                resetWindow();
        }
    }
    return choice;
}

void SettingsWindow::update(float dt)
{
    updateHover();
}

void SettingsWindow::render()
{
    m_window.draw(m_title);
    m_window.draw(m_gameSoundText);
    m_window.draw(m_playerNameText);
    m_window.draw(m_backButtonText);
}

void SettingsWindow::resetWindow()
{
    m_settingHover = Setting::NONE;
}

void SettingsWindow::updateHover()
{
    resetHover();
    switch (m_settingHover) {
    case Setting::GAMESOUND:
        m_gameSoundText.setFillColor(sf::Color::White);
        break;
    case Setting::PLAYERNAME:
        m_playerNameText.setFillColor(sf::Color::White);
        break;
    case Setting::BACK:
        m_backButtonText.setFillColor(sf::Color::White);
        break;
    case Setting::NONE:
        break;
    }
}

void SettingsWindow::resetHover()
{
    m_gameSoundText.setFillColor(sf::Color(100, 100, 100));
    m_playerNameText.setFillColor(sf::Color(100, 100, 100));
    m_backButtonText.setFillColor(sf::Color(100, 100, 100));
}