#pragma once

#include "Window.h"
#include "CollisionHandler.h"
#include "GameClock.h"
#include "Platform.h"
#include "Brick.h"
#include "Ball.h"

#include <memory>
#include <list>

const int NUM_OF_BRICKS = 12;

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
	
	void resetWindow();

private:
	// game window
	sf::Text m_title;
	sf::RectangleShape m_elementWindow;
	sf::Text m_scoreText;
	sf::Text m_timeText;

	// elements
	std::list<std::shared_ptr<Ball>> m_balls;
	std::vector<std::shared_ptr<Brick>> m_bricks;
	int m_ballSpeed;

	void releaseBalls(float dt);
	void initBricks(int numOfBricks);
	bool m_releasePressed;

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
	bool m_gamePaused;
	GameState m_gameState;
	PauseChoice m_pauseChoice;
};