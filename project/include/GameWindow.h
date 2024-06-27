#pragma once

#include "Window.h"
#include "CollisionHandler.h"
#include "Platform.h"
#include "Brick.h"
#include "Ball.h"

#include <memory>
#include <list>

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

	void resetWindow();
	void updateHover();

	bool m_gamePaused;
	PauseChoice m_pauseChoice;
};