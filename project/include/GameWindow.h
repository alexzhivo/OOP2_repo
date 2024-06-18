#pragma once

#include <memory>
#include "Window.h"
#include "Ball.h"

enum class PauseChoice {
	GAME,
	MENU
};

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
	std::unique_ptr<Ball> m_ball;
	void recreateBall();

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