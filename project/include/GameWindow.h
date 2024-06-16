#pragma once

#include "Window.h"

enum class PauseChoice {
	GAME,
	MENU
};

class GameWindow : public Window {
public:
	GameWindow(sf::RenderWindow& window);

	UserChoice handleInput(sf::Event& event);
	void update();
	void render();

private:
	// game window
	sf::Text m_title;

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