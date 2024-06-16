#pragma once

#include "Window.h"

class StartWindow : public Window {
public:
	StartWindow(sf::RenderWindow& window);

	UserChoice handleInput(sf::Event& event);
	void update();
	void render();

private:
	sf::Text m_title;
	sf::Text m_subtext;

	sf::Font m_font;
};