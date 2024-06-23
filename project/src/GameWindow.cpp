#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    :   Window(window,objectCreator), 
        m_gamePaused(false), 
        m_pauseChoice(PauseChoice::GAME),
        m_ballSpeed(100)
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

    // Set up element window
    m_elementWindow.setFillColor(sf::Color(200, 200, 200));
    m_elementWindow.setOutlineThickness(2);
    m_elementWindow.setOutlineColor(sf::Color::White);
    m_elementWindow.setPosition(200.f, 250.f);
    m_elementWindow.setSize(sf::Vector2f(800.f, 600.f));

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

    recreateBalls();
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

void GameWindow::update(float dt)
{
    // HOVER
    updateHover();

    // BALLS
    for (auto& ball : m_balls) {
        ball->update(dt);
        if (m_gamePaused) {
            ball->setVelocityZero();
        }
        else {
            ball->restoreVelocity();
        }
    }
    // PLATFORM
    if (!m_gamePaused) {
        m_platform.update(dt);
    }

    // COLLISIONS
    m_collisionHandler.handleOutOfBoarder(m_balls, m_platform.getShape(), m_elementWindow);
    m_collisionHandler.handleBallPlatform(m_balls, m_platform.getShape());
}

void GameWindow::render()
{
    m_window.draw(m_elementWindow);     // Window For Balls

    m_platform.draw(m_window);          // Platform

    for (auto& ball : m_balls) {        // Balls
        ball->draw(m_window);
    }
    m_window.draw(m_title);             // Title
    if (m_gamePaused) {                 // Pause Menu
        m_window.draw(m_pauseWindow);
        m_window.draw(m_pauseText);
        m_window.draw(m_returnToGameText);
        m_window.draw(m_BackToMenuText);
    }
}

void GameWindow::recreateBalls()
{
    m_balls.clear();
    for (int i = 0; i < NUM_OF_BALLS; ++i)
        m_balls.push_back(std::make_unique<Ball>(sf::Vector2f(300.f + i * 100, 300.f),sf::Vector2f(3.f * m_ballSpeed, 3.f * m_ballSpeed)));
}

void GameWindow::resetWindow()
{
    m_gamePaused = false;
    m_pauseChoice = PauseChoice::GAME;
    recreateBalls();
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