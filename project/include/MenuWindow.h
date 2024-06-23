#pragma once

#include "Window.h"

// Menu Buttons
constexpr int NUM_OF_BUTTONS = 5;

enum class MenuButton {
	PLAY,
	LEADERBOARD,
	HELP,
	SETTINGS,
	EXIT,
	NONE
};

// operators for enum class
MenuButton& operator++(MenuButton& button);
MenuButton& operator--(MenuButton& button);

class MenuWindow : public Window {
public:
	MenuWindow(sf::RenderWindow& window, ObjectCreator* objectCreator);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

private:
	sf::Text m_title;
	sf::Text m_playButton;
	sf::Text m_leaderboardButton;
	sf::Text m_helpButton;
	sf::Text m_settingsButton;
	sf::Text m_exitButton;

	void resetWindow();

	// hover effect
	MenuButton m_currHoverButton;
	void updateHover();
	void resetAllButtons();
};