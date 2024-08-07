#pragma once

#include "Window.h"

class HelpWindow : public Window {
public:
	HelpWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

private:
	sf::Sprite& m_helpSprite;
	sf::Text m_backButton;

	void resetWindow();

	// hover effect
	bool m_currBackButton;
	void updateHover();
};