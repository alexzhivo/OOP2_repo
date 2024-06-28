#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    : Window(window, objectCreator),
        m_gameState(GameState::NOT_ENDED),
        m_gamePaused(false), 
        m_releasePressed(false),
        m_pauseChoice(PauseChoice::GAME),
        m_ballSpeed(100),
        m_score(0)
{
    // Set up title
    m_title = objectCreator->createTextButton("GamePlayScreen", 30, 'W', 10.f, 10.f);

    // Set up element window
    m_elementWindow = objectCreator->createRectangle(879.f, 800.f, 'C', 210.f, 60.f);

    // Set up game text
    m_scoreText = objectCreator->createTextButton("", 20, 'W', 20.f, 100.f);

    // Set up pause screen
    m_pauseWindow = objectCreator->createRectangle(600.f, 750.f, 'M', 350.f, 100.f);

    m_pauseText = objectCreator->createTextButton("PAUSED", 50, 'W', 550.f, 200.f);
    m_returnToGameText = objectCreator->createTextButton("continue game", 40, 'W', 510.f, 400.f);
    m_BackToMenuText = objectCreator->createTextButton("return to menu", 40, 'W', 510.f, 500.f);

    initBricks(NUM_OF_BRICKS);

    m_platform.initStickyBall();
}

UserChoice GameWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (!m_gamePaused) {    // GAME IS ACTIVE
            if (event.key.code == sf::Keyboard::Escape) {   // enter pause mode
                m_gamePaused = true;
            }
            else if (event.key.code == sf::Keyboard::Space) {   // release balls
                m_releasePressed = true;
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

    if (m_releasePressed) {
        releaseBalls(dt);        
        m_releasePressed = false;
    }

    // BRICKS
    if (!m_gamePaused) {
        for (auto& brick : m_bricks)
            brick->update(dt);
    }

    // GAME WON
    if (m_bricks.empty())
        m_gameState = GameState::ENDED_WIN;

    // COLLISIONS
    m_collisionHandler.handleOutOfBoarder(m_balls, m_platform.getShape(), m_elementWindow);
    m_collisionHandler.handleBallPlatform(m_balls, m_platform.getShape());
    if (m_collisionHandler.handleBallBrick(m_balls, m_bricks))
        m_score += 125;

    // SCORE
    m_scoreText.setString("SCORE : " + std::to_string(m_score));
}

void GameWindow::render()
{
    m_window.draw(m_elementWindow);     // Window For Balls

    m_window.draw(m_scoreText);         // Window Text

    m_platform.draw(m_window);          // Platform

    for (auto& brick : m_bricks)        // Bricks
        brick->draw(m_window);

    for (auto& ball : m_balls)          // Balls
        ball->draw(m_window);

    m_window.draw(m_title);             // Title
    if (m_gamePaused) {                 // Pause Menu
        m_window.draw(m_pauseWindow);
        m_window.draw(m_pauseText);
        m_window.draw(m_returnToGameText);
        m_window.draw(m_BackToMenuText);
    }
}

GameState GameWindow::getGameState() const
{
    return m_gameState;
}

int GameWindow::getScore() const
{
    return m_score;
}

void GameWindow::releaseBalls(float dt)
{
    for (int i = 0; i < m_platform.getStickyBallsNum(); i++) {
        auto ball = m_platform.releaseBall();

        int seed = (int)(dt * 100000) % 100;
        std::srand(seed);
        float random_num = static_cast<float>(std::rand()) / 400;
        float scaled_num = (random_num * 1.6f) - 0.8f;

        ball->release(scaled_num);
        m_balls.push_back(ball);
    }
}

void GameWindow::initBricks(int numOfBricks)
{
    int space = 3;
    float brick_width = 70;
    float brick_height = 30;
    float window_x_pos = m_elementWindow.getPosition().x;
    float newXPos = window_x_pos;
    float window_width = m_elementWindow.getSize().x;
    float newYPos = m_elementWindow.getPosition().y + 200;


    for (int i = 0; i < numOfBricks; i++) {
        newXPos += space;
        if (window_width + window_x_pos <= newXPos) {
            newXPos -= window_width;
            newXPos += space;
            newYPos += brick_height;
            newYPos += space;
        }
        m_bricks.push_back(std::make_shared<Brick>(1, newXPos, newYPos, brick_width, brick_height));
        newXPos += brick_width;
    }
}

void GameWindow::resetWindow()
{
    m_gameState = GameState::NOT_ENDED;
    m_gamePaused = false;
    m_pauseChoice = PauseChoice::GAME;
    m_balls.clear();
    m_bricks.clear();
    initBricks(NUM_OF_BRICKS);
    m_platform.reset();
    m_score = 0;
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