#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window)
    : Window(window), m_gamePaused(false), m_pauseChoice(PauseChoice::GAME)
{
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Handle font loading error
    }

    // Set up title
    m_title.setFont(m_font);
    m_title.setString("GAMEPLAY");
    m_title.setCharacterSize(100);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(300.f, 100.f);

    // Set up pause screen
    m_pauseWindow.setFillColor(sf::Color::White);
    m_pauseWindow.setPosition(100.f, 300.f);
    m_pauseWindow.setSize(sf::Vector2f(200.f, 200.f));

    m_pauseText.setFont(m_font);
    m_pauseText.setString("game paused");
    m_pauseText.setCharacterSize(20);
    m_pauseText.setFillColor(sf::Color::Black);
    m_pauseText.setPosition(100.f, 300.f);

    m_returnToGameText.setFont(m_font);
    m_returnToGameText.setString("return to game");
    m_returnToGameText.setCharacterSize(20);
    m_returnToGameText.setFillColor(sf::Color::Black);
    m_returnToGameText.setPosition(100.f, 320.f);

    m_BackToMenuText.setFont(m_font);
    m_BackToMenuText.setString("back to menu");
    m_BackToMenuText.setCharacterSize(20);
    m_BackToMenuText.setFillColor(sf::Color::Black);
    m_BackToMenuText.setPosition(100.f, 340.f);
}

UserChoice GameWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (!m_gamePaused) {    // GAME IS ACTIVE
            if (event.key.code == sf::Keyboard::Escape) {   // enter pause mode
                m_gamePaused = true;
            }
            else if (event.key.code == sf::Keyboard::W) {
                choice.isSelected = true;
                choice.nextWindow = WindowState::FINISH;  // to finish
                resetWindow();
            }
        }
        else {                  // GAME IS PAUSED
            if (event.key.code == sf::Keyboard::Escape) {   // back to game
                m_gamePaused = false;
            }
            else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                if (m_pauseChoice == PauseChoice::GAME)
                    m_pauseChoice = PauseChoice::MENU;
                else
                    m_pauseChoice = PauseChoice::GAME;
            }
            else if (event.key.code == sf::Keyboard::Enter) {   
                if (m_pauseChoice == PauseChoice::GAME)     // back to game
                    m_gamePaused = false;
                else {
                    choice.isSelected = true;
                    choice.nextWindow = WindowState::MENU;  // back to menu
                    resetWindow();
                }
            }
        }
    }
    return choice;
}

void GameWindow::update()
{
    updateHover();
}

void GameWindow::render()
{
    m_window.draw(m_title);
    if (m_gamePaused) {
        m_window.draw(m_pauseWindow);
        m_window.draw(m_pauseText);
        m_window.draw(m_returnToGameText);
        m_window.draw(m_BackToMenuText);
    }
}

void GameWindow::resetWindow()
{
    m_gamePaused = false;
    m_pauseChoice = PauseChoice::GAME;
}

void GameWindow::updateHover()
{
    if (m_pauseChoice == PauseChoice::GAME) {
        m_returnToGameText.setFillColor(sf::Color::Red);
        m_BackToMenuText.setFillColor(sf::Color::Black);
    }
    else {
        m_returnToGameText.setFillColor(sf::Color::Black);
        m_BackToMenuText.setFillColor(sf::Color::Red);

    }
}