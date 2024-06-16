#pragma once

#include "Window.h"

class FinishWindow : public Window {
public:
	FinishWindow(sf::RenderWindow& window);

	UserChoice handleInput(sf::Event& event);
	void update();
	void render();

private:
	sf::Text m_title;

	void resetWindow();

	sf::Font m_font;
};