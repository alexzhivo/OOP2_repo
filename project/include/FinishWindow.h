#pragma once

#include "Window.h"

class FinishWindow : public Window {
public:
	FinishWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

	void setScore(int score);
	void setTitle(std::string text);

private:
	sf::Text m_title;
	sf::Text m_scoreText;

	void resetWindow();
};