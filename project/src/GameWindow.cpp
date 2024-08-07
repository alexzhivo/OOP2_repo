#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager)
    : Window(window, objectCreator, soundManager),
    m_gameState(GameState::NOT_ENDED),
    m_gamePaused(false),
    m_releasePressed(false),
    m_pauseChoice(PauseChoice::GAME),
    m_ballSpeed(100),
    m_score(0),
    m_life(5),
    m_currLevel(1),
    m_platform(objectCreator->getSprite("platform")),
    m_bigBall(false)
{
    // Set up random seed
    srand(static_cast<unsigned int>(time(0)));

    // Set up element window
    m_elementWindow = objectCreator->createRectangle(879.f, 800.f, "dark_blue", 210.f, 60.f);

    // Set up game text
    m_levelText = objectCreator->createText("", 20, "white", 10.f, 10.f);
    m_timeText = objectCreator->createText("", 20, "white", 550.f, 10.f);
    m_scoreText = objectCreator->createText("", 20, "white", 10.f, 875.f);
    m_bestScoreText = objectCreator->createText("", 20, "white", 900.f, 875.f);

    // Set up pause screen
    m_pauseWindow = objectCreator->createRectangle(600.f, 750.f, "black_t", 350.f, 100.f);

    m_pauseText = objectCreator->createText("PAUSED", 40, "white", 480.f, 200.f);
    m_returnToGameText = objectCreator->createText("CONTINUE GAME", 30, "white", 440.f, 400.f);
    m_BackToMenuText = objectCreator->createText("RETURN TO MENU", 30, "white", 440.f, 500.f);

    initLevel(1);

    m_platform.initStickyBall(objectCreator->getSprite("ball"));

    m_gameClock.initTime(TIMER_IN_SEC);
}

UserChoice GameWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (!m_gamePaused) {    // GAME IS ACTIVE
            if (event.key.code == sf::Keyboard::Escape) {   // enter pause mode
                m_soundManager->playSound("select", false);
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
                m_soundManager->playSound("hover", false);
                if (m_pauseChoice == PauseChoice::GAME)
                    m_pauseChoice = PauseChoice::MENU;
                else
                    m_pauseChoice = PauseChoice::GAME;
            }
            else if (event.key.code == sf::Keyboard::Enter) {   
                m_soundManager->playSound("select", false);
                if (m_pauseChoice == PauseChoice::GAME)     // back to game
                    m_gamePaused = false;
                else {
                    choice.isSelected = true;
                    choice.nextWindow = WindowState::MENU;  // back to menu
                    this->reset();
                }
            }
        }
    }
    return choice;
}

void GameWindow::update(float dt)
{
    handleCollisions(dt);

    if (m_balls.empty() && m_platform.getStickyBallsNum() == 0) {
        m_life--;
        m_bigBall = false;
        m_soundManager->playSound("lose_ball", false);
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
            if (m_bigBall && ball->getPower() == 1)
                ball->makeBig(m_objectCreator->getSprite("big_ball"));
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

    // NEXT LEVEL
    if (m_bricks.empty() && m_gameState == GameState::NOT_ENDED)
        m_gameState = GameState::NEXT_LEVEL;

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
    drawPowers();
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
    auto list = m_platform.getListOfStickyBalls();
    auto stickyList = static_cast<std::list<std::shared_ptr<Ball>>*>(list);

    while (!stickyList->empty()) {

        int seed = (int)(dt * 100000) % 100;
        std::srand(seed);
        float random_num = static_cast<float>(std::rand()) / 400;
        float scaled_num = (random_num * 1.6f) - 0.8f;

        auto it = stickyList->begin();
        std::shared_ptr<Ball> ball = *it;
        stickyList->erase(it);
        ball->release(scaled_num);
        m_platform.setSticky(false);
        m_balls.push_back(ball);
    }
}

bool GameWindow::initLevel(int level)
{
    int space = 3;
    float brick_width = 70;
    float brick_height = 30;
    float window_x_pos = m_elementWindow.getPosition().x;
    float newXPos = window_x_pos;
    float window_width = m_elementWindow.getSize().x;
    float newYPos = m_elementWindow.getPosition().y + space;

    std::string filename = "level_" + std::to_string(level) + ".txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening : " + filename + "\n";
        return false;
    }
    else {
        m_levelText.setString("LEVEL: " + std::to_string(level));
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
    m_gameState = GameState::NOT_ENDED;
    return true;
}

void GameWindow::chanceForGift(float pos_x, float pos_y)
{
    double randomSpawn = static_cast<double>(rand()) / RAND_MAX;
    auto randomPower = (PowerType)(rand() % 9);
    if (randomSpawn < 0.2) {
        switch (randomPower) {
        case PowerType::ADD_PTS:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_upscore")));
            return;
        case PowerType::DEC_PTS:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_lowscore")));
            return;
        case PowerType::SPLIT:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_split")));
            return;
        case PowerType::ADD_LIFE:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_add_life")));
            return;
        case PowerType::DEC_LIFE:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_dec_life")));
            return;
        case PowerType::BIG_BALL:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_inc_ball")));
            return;
        case PowerType::STICKY:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_sticky")));
            return;
        case PowerType::SHORT:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_short")));
            return;
        case PowerType::LONG:
            m_powers.push_back(std::make_shared<PowerUp>(randomPower, sf::Vector2f(pos_x + 18, pos_y + 10), m_objectCreator->getSprite("power_long")));
            return;
        }
    }
}

void GameWindow::handleCollisions(float dt)
{
    m_collisionHandler.handleBallPlatform(m_balls, m_platform);
    BrickInfo info = m_collisionHandler.handleBallBrick(m_balls, m_bricks);
    switch (info.cond) {
    case BrickCondition::HIT:
        m_soundManager->playSound("not_break", false);
        m_score += 75;
        break;
    case BrickCondition::BREAK:
        m_soundManager->playSound("pop_once", false);
        m_score += 150;
        chanceForGift(info.pos_x, info.pos_y);
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
        m_soundManager->playSound("add_pts", false);
        break;
    case PowerType::DEC_PTS:
        m_score -= 1000;
        m_soundManager->playSound("lose_ball", false);
        break;
    case PowerType::SPLIT:
        splitBalls();
        m_soundManager->playSound("pop_once", false);
        break;
    case PowerType::ADD_LIFE:
        if (m_life < 5) {
            m_life++;
        }
        m_soundManager->playSound("add_pts", false);
        break;
    case PowerType::DEC_LIFE:
        m_life--;
        if (m_life < 0) {
            m_gameState = GameState::ENDED_LIVE;
        }
        m_soundManager->playSound("lose_ball", false);
        break;
    case PowerType::STICKY:
        m_platform.setSticky(true);
        m_soundManager->playSound("add_pts", false);
        break;
    case PowerType::SHORT:
        if (m_platform.isSticky())
            releaseBalls(dt);
        m_platform.makeShort(m_objectCreator->getSprite("platform_sm"),
            m_objectCreator->getSprite("platform"));
        m_soundManager->playSound("add_pts", false);
        break;
    case PowerType::LONG:
        m_platform.makeLong(m_elementWindow,
            m_objectCreator->getSprite("platform_long"),
            m_objectCreator->getSprite("platform"));
        m_soundManager->playSound("add_pts", false);
        break;
    case PowerType::BIG_BALL:
        m_bigBall = true;
        m_soundManager->playSound("add_pts", false);
        break;
    case PowerType::EMPTY:
        break;
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

void GameWindow::drawPowers()
{
    sf::Sprite sprite;
    sprite.setScale(2.f, 2.f);

    int powerCount = 0;

    if (m_platform.isShort()) {
        sprite.setTexture(m_objectCreator->getTexture("power_short"));
        sprite.setPosition(8.f + 40.f * powerCount, 80.f);
        m_window.draw(sprite);
        powerCount++;
    }
    if (m_platform.isLong()) {
        sprite.setTexture(m_objectCreator->getTexture("power_long"));
        sprite.setPosition(8.f + 40.f * powerCount, 80.f);
        m_window.draw(sprite);
        powerCount++;
    }
    if (m_platform.isSticky()) {
        sprite.setTexture(m_objectCreator->getTexture("power_sticky"));
        sprite.setPosition(8.f + 40.f * powerCount, 80.f);
        m_window.draw(sprite);
        powerCount++;
    }
    if (m_bigBall) {
        sprite.setTexture(m_objectCreator->getTexture("power_inc_ball"));
        sprite.setPosition(8.f + 40.f * powerCount, 80.f);
        m_window.draw(sprite);
        powerCount++;
    }
}

void GameWindow::setupNextLevel()
{
    if (!initLevel(m_currLevel + 1)) {
        m_gameState = GameState::ENDED_WIN;
    }
    else {
        m_currLevel++;
        softReset();
        m_soundManager->playSound("level_up", false);
    }
}

void GameWindow::reset()
{
    m_gameState = GameState::NOT_ENDED;
    m_gamePaused = false;
    m_pauseChoice = PauseChoice::GAME;
    m_bricks.clear();
    m_currLevel = 1;
    initLevel(m_currLevel);
    m_score = 0;
    m_life = 5;
    softReset();
}

void GameWindow::softReset()
{
    m_balls.clear();
    m_powers.clear();
    m_platform.reset(m_objectCreator->getSprite("ball"),m_objectCreator->getSprite("platform"),m_elementWindow);
    m_bigBall = false;
    m_gameClock.initTime(TIMER_IN_SEC);
}

void GameWindow::splitBalls()
{
    if (m_balls.empty()) {
        if (m_platform.getStickyBallsNum()) {
            m_platform.splitSticky(m_objectCreator->getSprite("ball"));
        }
        return;
    }

    if (m_balls.size() > 10)
        return;

    sf::Vector2f position;
    sf::Vector2f velocity;
    
    auto size = m_balls.size();
    auto iter = m_balls.begin();
    for (int i = 0; i < size; i++) {
        position = (*iter)->getSprite().getPosition();
        velocity = (*iter)->getVelocity();
        velocity.y = -velocity.y;
        (*iter)->setVelocity(velocity);
        m_balls.push_back(std::make_shared<Ball>(position, sf::Vector2f(-90.3116f, -286.084f), m_objectCreator->getSprite("ball")));
        m_balls.push_back(std::make_shared<Ball>(position, sf::Vector2f(133.698f, -268.561f), m_objectCreator->getSprite("ball")));
        ++iter;
    }
}

void GameWindow::updateHover()
{
    if (m_pauseChoice == PauseChoice::GAME) {
        m_returnToGameText.setFillColor(m_objectCreator->getColor("red"));
        m_BackToMenuText.setFillColor(m_objectCreator->getColor("white"));
    }
    else {
        m_returnToGameText.setFillColor(m_objectCreator->getColor("white"));
        m_BackToMenuText.setFillColor(m_objectCreator->getColor("red"));
    }
}