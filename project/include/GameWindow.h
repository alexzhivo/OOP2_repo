#pragma once

#include "Window.h"
#include "CollisionHandler.h"
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

class GameWindow : public Window {
public:
	GameWindow(sf::RenderWindow& window, ObjectCreator* objectCreator);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();
	
	bool isGameWon() const;
	void resetWindow();

private:
	// game window
	sf::Text m_title;
	sf::RectangleShape m_elementWindow;

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

	bool m_gamePaused;
	bool m_gameWon;
	PauseChoice m_pauseChoice;
};