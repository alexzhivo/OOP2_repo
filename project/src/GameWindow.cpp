#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    : Window(window, objectCreator),
    m_gameState(GameState::NOT_ENDED),
    m_gamePaused(false),
    m_releasePressed(false),
    m_pauseChoice(PauseChoice::GAME),
    m_ballSpeed(100),
    m_score(0),
    m_life(5),
    m_currLevel(1),
    m_platform(objectCreator->getSprite("platform_mid"))
{
    // Set up random seed
    srand(static_cast<unsigned int>(time(0)));

    // Set up element window
    m_elementWindow = objectCreator->createRectangle(879.f, 800.f, 'D', 210.f, 60.f);

    // Set up game text
    m_levelText = objectCreator->createTextButton("", 20, 'W', 10.f, 10.f);
    m_timeText = objectCreator->createTextButton("", 20, 'W', 550.f, 10.f);
    m_scoreText = objectCreator->createTextButton("", 20, 'W', 10.f, 875.f);
    m_bestScoreText = objectCreator->createTextButton("", 20, 'W', 900.f, 875.f);

    // Set up pause screen
    m_pauseWindow = objectCreator->createRectangle(600.f, 750.f, 'M', 350.f, 100.f);

    m_pauseText = objectCreator->createTextButton("PAUSED", 40, 'W', 480.f, 200.f);
    m_returnToGameText = objectCreator->createTextButton("CONTINUE GAME", 30, 'W', 440.f, 400.f);
    m_BackToMenuText = objectCreator->createTextButton("RETURN TO MENU", 30, 'W', 440.f, 500.f);

    initLevel();

    m_platform.initStickyBall(objectCreator->getSprite("ball"));

    m_gameClock.initTime(TIMER_IN_SEC);
}

UserChoice GameWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (!m_gamePaused) {    // GAME IS ACTIVE
            if (event.key.code == sf::Keyboard::Escape) {   // enter pause mode
                m_gamePaused = true;
            }
            if (event.key.code == sf::Keyboard::Space) {   // release balls
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
    // COLLISIONS
    m_collisionHandler.handleBallPlatform(m_balls, m_platform.getRect());
    BrickInfo info = m_collisionHandler.handleBallBrick(m_balls, m_bricks);
    switch (info.cond) {
    case BrickCondition::HIT:
        m_score += 75;
        break;
    case BrickCondition::BREAK:
        m_score += 150; 
        chanceForGift(info.pos_x,info.pos_y);
        break;
    case BrickCondition::NO_TOUCH:
        break;
    }
    m_collisionHandler.handleOutOfBoarder(m_balls, m_elementWindow);
    m_collisionHandler.handlePowerUpWindow(m_powers, m_elementWindow);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_platform.move(-600.f * dt, 0.0f); // Move left
        if (m_collisionHandler.handlePlatformWindow(m_platform.getRect(), m_elementWindow))
            m_platform.move(600.f * dt, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_platform.move(600.0f * dt, 0.0f); // Move right
        if (m_collisionHandler.handlePlatformWindow(m_platform.getRect(), m_elementWindow))
            m_platform.move(-600.f * dt, 0.0f);
    }

    switch (m_collisionHandler.handlePowerPlatform(m_powers, m_platform.getRect())) {
    case PowerType::ADD_PTS:
        m_score += 1000;
        break;
    case PowerType::DEC_PTS:
        m_score -= 1000;
        break;
    case PowerType::EMPTY:
        break;
    }

    if (m_balls.empty() && m_platform.getStickyBallsNum() == 0) {
        m_life--;
        if (m_life < 0)
            m_gameState = GameState::ENDED_LIVE;
        else {
            m_platform.initStickyBall(m_objectCreator->getSprite("ball"));
        }
    }

    // HOVER
    updateHover();

    // BALLS
    if (!m_balls.empty()) {
        for (auto& ball : m_balls) {
            ball->update(dt);
            if (m_gamePaused) {
                ball->setVelocityZero();
            }
            else {
                ball->restoreVelocity();
            }
        }
    }

    // PLATFORM
    if (!m_gamePaused) {
        m_platform.update(dt);
    }

    if (!m_gamePaused) {
        for (auto& power : m_powers)
            power->update(dt);
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

    // SCORE
    m_scoreText.setString("SCORE: " + std::to_string(m_score));

    // TIME
    if (m_gamePaused)
        m_gameClock.stopTime();
    else {
        m_gameClock.startTime();
        m_timeText.setString("TIME:" + m_gameClock.getTimeString());
    }

    if (m_gameClock.isTimeZero()) {   // TIME IS ENDED
        m_gameState = GameState::ENDED_TIME;
        return;
    }
}

void GameWindow::render()
{
    m_window.draw(m_elementWindow);     // Window For Balls

    m_window.draw(m_scoreText);         // Window Text
    m_window.draw(m_timeText);
    m_window.draw(m_levelText);
    drawLives();
    m_window.draw(m_bestScoreText);


    for (auto& brick : m_bricks)        // Bricks
        brick->draw(m_window);

    for (auto& power : m_powers)        // Powers
        power->draw(m_window);

    for (auto& ball : m_balls)          // Balls
        ball->draw(m_window);

    m_platform.draw(m_window);          // Platform

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

void GameWindow::updateBestScore(int score)
{
    m_bestScoreText.setString("BEST SCORE: " + std::to_string(score));
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

void GameWindow::initLevel()
{
    int space = 3;
    float brick_width = 70;
    float brick_height = 30;
    float window_x_pos = m_elementWindow.getPosition().x;
    float newXPos = window_x_pos;
    float window_width = m_elementWindow.getSize().x;
    float newYPos = m_elementWindow.getPosition().y + space;

    std::string filename = "level_" + std::to_string(m_currLevel) + ".txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening : " + filename + "\n";
        return;
    }
    else {
        m_levelText.setString("LEVEL: " + std::to_string(m_currLevel));
        std::string line;
        while (std::getline(file, line)) {

            for (char c : line) {
                int blockType = c - '0';  // convert from char to int
                newXPos += space;
                if (window_width + window_x_pos <= newXPos) {
                    newXPos -= window_width;
                    newXPos += space;
                    newYPos += brick_height;
                    newYPos += space;
                }
                switch (blockType) {
                case 1:
                    m_bricks.push_back(std::make_shared<Brick>(blockType, newXPos, newYPos, brick_width, brick_height, m_objectCreator->getSprite("brick_blue")));
                    break;
                case 2:
                    m_bricks.push_back(std::make_shared<Brick>(blockType, newXPos, newYPos, brick_width, brick_height, m_objectCreator->getSprite("brick_green")));
                    break;
                case 3:
                    m_bricks.push_back(std::make_shared<Brick>(blockType, newXPos, newYPos, brick_width, brick_height, m_objectCreator->getSprite("brick_red")));
                    break;
                }
                newXPos += brick_width;
            }
        }
        file.close();
    }
}

void GameWindow::chanceForGift(float pos_x, float pos_y)
{
    double randomSpawn = static_cast<double>(rand()) / RAND_MAX;
    auto randomPower = (PowerType)(rand() % 2);
    if (randomSpawn < 0.15) {
        if (randomPower == PowerType::ADD_PTS) {
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_upscore")));
            return;
        } 
        if (randomPower == PowerType::DEC_PTS) {
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_lowscore")));
            return;
        }
    }
}

void GameWindow::drawLives()
{
    sf::Sprite& lifeSprite = m_objectCreator->getSprite("heart_red");
    sf::Sprite& noLifeSprite = m_objectCreator->getSprite("heart_blue");

    for (int index = 0; index < 5; index++) {
        if (index + 1 > m_life) {
            noLifeSprite.setPosition(8.f + (index * 30), 40.f);
            noLifeSprite.setScale(3.f, 3.f);
            m_window.draw(noLifeSprite);
        }
        else {
            lifeSprite.setPosition(8.f + (index * 30), 40.f);
            lifeSprite.setScale(3.f, 3.f);
            m_window.draw(lifeSprite);
        }
    }
}


void GameWindow::resetWindow()
{
    m_gameState = GameState::NOT_ENDED;
    m_gamePaused = false;
    m_pauseChoice = PauseChoice::GAME;
    m_balls.clear();
    m_bricks.clear();
    m_powers.clear();
    initLevel();
    m_platform.reset(m_objectCreator->getSprite("ball"));
    m_score = 0;
    m_currLevel = 1;
    m_life = 5;
    m_gameClock.initTime(TIMER_IN_SEC);
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