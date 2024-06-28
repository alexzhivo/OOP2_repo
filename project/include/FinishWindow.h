#pragma once

#include "Window.h"

class FinishWindow : public Window {
public:
	FinishWindow(sf::RenderWindow& window, ObjectCreator* objectCreator);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

	void setScore(int score);

private:
	sf::Text m_title;
	sf::Text m_scoreText;

	void resetWindow();
};