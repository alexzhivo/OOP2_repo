#pragma once

#include "Window.h"

class StartWindow : public Window {
public:
	StartWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager);

	UserChoice handleInput(sf::Event& event);
	void update(float dt);
	void render();

private:
	sf::Sprite m_wallpaper;
	sf::Sprite m_title;
	sf::Text m_version;
	sf::Text m_subtext;

	void runWallpaper();
};