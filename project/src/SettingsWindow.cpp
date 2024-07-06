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

SettingsWindow::SettingsWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager)
    : Window(window,objectCreator,soundManager), m_settingHover(Setting::NONE), m_isGameSoundOn(true)
    , m_isEditName(false)
{
    // default player name
    m_playerName = "NewPlayer";

    m_title = objectCreator->createText("SETTINGS", 80, "white", 280.f, 200.f);
    m_gameSoundText = objectCreator->createText("Game Sound : ON", 30, "dark_grey", 400.f, 400.f);
    m_playerNameText = objectCreator->createText("Player Name : " + m_playerName, 30, "dark_grey", 250.f, 500.f);
    m_backButtonText = objectCreator->createText("<< BACK >>", 30, "dark_grey", 400.f, 600.f);
}

UserChoice SettingsWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (m_isEditName) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) { // Only consider ASCII characters
                char enteredChar = static_cast<char>(event.text.unicode);

                // Check if entered character is alphanumeric & namelimit
                if (std::isalnum(enteredChar) && m_playerName.size() < 16) {
                    m_playerName += enteredChar;
                }
                // Handle backspace (ASCII 8)
                else if (enteredChar == 8 && !m_playerName.empty()) {
                    m_playerName.pop_back();
                }
                m_playerNameText.setString("Player Name : " + m_playerName);
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (m_isEditName) {
            if (event.key.code == sf::Keyboard::Enter) {
                m_soundManager->playSound("select", false);
                m_isEditName = false;
                updateHover();
            }
        }
        else {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                m_soundManager->playSound("hover", false);
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
                m_soundManager->playSound("select", false);
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

std::string SettingsWindow::getPlayerName() const
{
    return m_playerName;
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
        m_gameSoundText.setFillColor(m_objectCreator->getColor("white"));
        break;
    case Setting::PLAYERNAME:
        if (m_isEditName) {
            m_playerNameText.setFillColor(m_objectCreator->getColor("green"));
        }
        else {
            m_playerNameText.setFillColor(m_objectCreator->getColor("white"));
        }
        break;
    case Setting::BACK:
        m_backButtonText.setFillColor(m_objectCreator->getColor("white"));
        break;
    case Setting::NONE:
        break;
    }
}

void SettingsWindow::resetHover()
{
    m_gameSoundText.setFillColor(m_objectCreator->getColor("dark_grey"));
    m_playerNameText.setFillColor(m_objectCreator->getColor("dark_grey"));
    m_backButtonText.setFillColor(m_objectCreator->getColor("dark_grey"));
}

void SettingsWindow::updateGameSound()
{
    if (m_isGameSoundOn)
        m_gameSoundText.setString("Game Sound : ON");
    else
        m_gameSoundText.setString("Game Sound : OFF");
}