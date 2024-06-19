#pragma once

#include "CollisionHandler.h"

#include <memory>
#include <list>
#include "Window.h"
#include "Ball.h"

enum class PauseChoice {
	GAME,
	MENU
};

constexpr int NUM_OF_BALLS = 1;

class GameWindow : public Window {
public:
	GameWindow(sf::RenderWindow& window);

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