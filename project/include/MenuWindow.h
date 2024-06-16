#pragma once

#include "Window.h"

enum class Button {
	PLAY,
	LEADERBOARD,
	HELP,
	SETTINGS,
	NONE
};

// operators for enum class
Button& operator++(Button& button);
Button& operator--(Button& button);

class MenuWindow : public Window {
public:
	MenuWindow(sf::RenderWindow& window);

	UserChoice handleInput(sf::Event& event);
	void update();
	void render();

private:
	sf::Text m_title;
	sf::Text m_playButton;
	sf::Text m_leaderboardButton;
	sf::Text m_helpButton;
	sf::Text m_settingsButton;

	void resetWindow();

	// hover effect
	Button m_currHoverButton;
	void updateHover();
	void resetAllButtons();

	sf::Font m_font;
};