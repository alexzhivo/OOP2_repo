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
	MenuWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

private:
	sf::Text m_title;

	// Buttons
	std::vector<sf::Text> m_buttons;
	MenuButton m_currHoverButton;

	void resetWindow();
	void updateHover();
	void resetAllButtons();
};