#pragma once

#include "Window.h"

class LeaderboardWindow : public Window {
public:
	LeaderboardWindow(sf::RenderWindow& window);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

private:
	sf::Text m_title;
	sf::Text m_backButton;

	void resetWindow();

	// hover effect
	bool m_currBackButton;
	void updateHover();

	sf::Font m_font;
};