#pragma once

#include "Window.h"
#include "CollisionHandler.h"
#include "Platform.h"
#include "Ball.h"

#include <memory>
#include <list>

enum class PauseChoice {
	GAME,
	MENU
};

constexpr int NUM_OF_BALLS = 10;

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

	// ball
	std::list<std::unique_ptr<Ball>> m_balls;
	void recreateBalls();
	int m_ballSpeed;

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

	sf::Font m_font;
};