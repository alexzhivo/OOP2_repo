#pragma once

#include "Window.h"
#include "CollisionHandler.h"
#include "GameClock.h"
#include "Platform.h"
#include "Brick.h"
#include "Ball.h"
#include "PowerUp.h"

const int TIMER_IN_SEC = 120;

enum class PauseChoice {
	GAME,
	MENU
};

enum class GameState {
	NOT_ENDED,
	ENDED_WIN,
	ENDED_TIME,
	ENDED_LIVE,
	NEXT_LEVEL
};

class GameWindow : public Window {
public:
	GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

	GameState getGameState() const;
	int getScore() const;
	void updateBestScore(int score);
	void setupNextLevel();
	
	void reset();


private:
	// User Interface
	sf::RectangleShape m_elementWindow;
	sf::Text m_scoreText;
	sf::Text m_timeText;
	sf::Text m_levelText;
	sf::Text m_bestScoreText;

	// data for elements
	std::list<std::shared_ptr<Ball>> m_balls;
	std::vector<std::shared_ptr<Brick>> m_bricks;
	std::vector<std::shared_ptr<PowerUp>> m_powers;

	void releaseBalls(float dt);
	bool initLevel(int level);
	void chanceForGift(float pos_x, float pos_y);
	void handleCollisions(float dt);
	void drawLives();
	void updateHover();
	void softReset();

	// platform
	Platform m_platform;

	// Collision Handler
	CollisionHandler m_collisionHandler;

	// pause window
	sf::RectangleShape m_pauseWindow;
	sf::Text m_pauseText;
	sf::Text m_returnToGameText;
	sf::Text m_BackToMenuText;


	// Clock
	GameClock m_gameClock;

	int m_score;
	int m_life;
	int m_currLevel;
	int m_ballSpeed;
	bool m_releasePressed;
	bool m_gamePaused;
	GameState m_gameState;
	PauseChoice m_pauseChoice;
};