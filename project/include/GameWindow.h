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
	ENDED_LIVE
};

class GameWindow : public Window {
public:
	GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

	GameState getGameState() const;
	int getScore() const;
	void updateBestScore(int score);
	
	void resetWindow();

private:
	// game window
	sf::RectangleShape m_elementWindow;
	sf::Text m_scoreText;
	sf::Text m_timeText;
	sf::Text m_levelText;
	sf::Text m_bestScoreText;

	// elements
	std::list<std::shared_ptr<Ball>> m_balls;
	std::vector<std::shared_ptr<Brick>> m_bricks;
	std::vector<std::shared_ptr<PowerUp>> m_powers;

	int m_ballSpeed;

	void releaseBalls(float dt);
	void initLevel();
	bool m_releasePressed;
	void chanceForGift(float pos_x, float pos_y);

	void drawLives();

	// platform
	Platform m_platform;

	// Collision Handler
	CollisionHandler m_collisionHandler;

	// pause window
	sf::RectangleShape m_pauseWindow;
	sf::Text m_pauseText;
	sf::Text m_returnToGameText;
	sf::Text m_BackToMenuText;

	void updateHover();

	// Clock
	GameClock m_gameClock;

	int m_score;
	int m_life;
	int m_currLevel;
	bool m_gamePaused;
	GameState m_gameState;
	PauseChoice m_pauseChoice;
};