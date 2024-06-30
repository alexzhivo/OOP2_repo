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
    : Window(window,objectCreator), m_settingHover(Setting::NONE), m_isGameSoundOn(true)
    , m_isEditName(false)
{
    // default player name
    m_playerName = "Challenger300624";

    m_title = objectCreator->createTextButton("SETTINGS", 100, 'W', 300.f, 200.f);
    m_gameSoundText = objectCreator->createTextButton("Game Sound : ON", 30, 'G', 500.f, 400.f);
    m_playerNameText = objectCreator->createTextButton("Player Name : " + m_playerName, 30, 'G', 450.f, 500.f);
    m_backButtonText = objectCreator->createTextButton("<< BACK >>", 30, 'G', 500.f, 600.f);
}

UserChoice SettingsWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (m_isEditName) {
        if (event.type == sf::Event::TextEntered) {
            std::cout << "textEnterd" << '\n';
            if (event.text.unicode < 128) { // Only consider ASCII characters
                char enteredChar = static_cast<char>(event.text.unicode);

                // Check if entered character is alphanumeric
                if (std::isalnum(enteredChar)) {
                    std::cout << "enterdChar" << '\n';
                    m_playerName += enteredChar;
                }
                // Handle backspace (ASCII 8)
                else if (enteredChar == 8 && !m_playerName.empty()) {
                    std::cout << "backspace" << '\n';
                    m_playerName.pop_back();
                }
                m_playerNameText.setString("Player Name : " + m_playerName);
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (m_isEditName) {
            if (event.key.code == sf::Keyboard::Enter) {
                m_isEditName = false;
                updateHover();
            }
        }
        else {
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
                updateHover();
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                if (m_settingHover == Setting::BACK) {
                    choice.isSelected = true;
                    choice.nextWindow = WindowState::MENU;
                    resetWindow();
                }
                else if (m_settingHover == Setting::GAMESOUND) {
                    m_isGameSoundOn = !m_isGameSoundOn;
                    updateGameSound();
                }
                else if (m_settingHover == Setting::PLAYERNAME) {
                    if (!m_isEditName) {
                        m_isEditName = true;
                        updateHover();
                    }
                }
            }
        }
    }
    return choice;
}

void SettingsWindow::update(float dt)
{
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
        if (m_isEditName) {
            m_playerNameText.setFillColor(sf::Color::Green);
        }
        else {
            m_playerNameText.setFillColor(sf::Color::White);
        }
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

void SettingsWindow::updateGameSound()
{
    if (m_isGameSoundOn)
        m_gameSoundText.setString("Game Sound : ON");
    else
        m_gameSoundText.setString("Game Sound : OFF");
}