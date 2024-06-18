#pragma once

#include "Window.h"

class HelpWindow : public Window {
public:
	HelpWindow(sf::RenderWindow& window);

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