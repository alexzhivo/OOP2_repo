#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    :   Window(window,objectCreator), 
        m_gamePaused(false), 
        m_pauseChoice(PauseChoice::GAME),
        m_ballSpeed(100)
{
    // Set up title
    m_title = objectCreator->createTextButton("GamePlayScreen", 30, 'W', 10.f, 10.f);

    // Set up element window
    m_elementWindow = objectCreator->createRectangle(800.f, 800.f, 'C', 250.f, 60.f);

    // Set up pause screen
    m_pauseWindow = objectCreator->createRectangle(600.f, 750.f, 'M', 350.f, 100.f);

    m_pauseText = objectCreator->createTextButton("PAUSED", 50, 'W', 550.f, 200.f);
    m_returnToGameText = objectCreator->createTextButton("continue game", 40, 'W', 510.f, 400.f);
    m_BackToMenuText = objectCreator->createTextButton("return to menu", 40, 'W', 510.f, 500.f);

    m_platform.initStickyBall();

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
            else if (event.key.code == sf::Keyboard::Space) {
                // release balls
                for (int i = 0; i < m_platform.getStickyBallsNum(); i++) {
                    auto ball = m_platform.releaseBall();
                    ball->setVelocity(sf::Vector2f(-300.f, -300.f));
                    m_balls.push_back(ball);   
                }
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
        m_balls.push_back(std::make_shared<Ball>(sf::Vector2f(300.f + i * 100, 300.f),sf::Vector2f(3.f * m_ballSpeed, 3.f * m_ballSpeed)));
}

void GameWindow::resetWindow()
{
    m_gamePaused = false;
    m_pauseChoice = PauseChoice::GAME;
    m_platform.reset();
    recreateBalls();
}

void GameWindow::updateHover()
{
    if (m_pauseChoice == PauseChoice::GAME) {
        m_returnToGameText.setFillColor(sf::Color::Red);
        m_BackToMenuText.setFillColor(sf::Color::White);
    }
    else {
        m_returnToGameText.setFillColor(sf::Color::White);
        m_BackToMenuText.setFillColor(sf::Color::Red);
    }
}