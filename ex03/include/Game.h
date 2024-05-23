#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "MenuWindow.h"
#include "GameWindow.h"
#include "EndingWindow.h"

const unsigned int WINDOW_WIDTH = 600,
				   WINDOW_HEIGTH = 800;

enum class GameState { MainMenu , Playing , Ending };

class Game {
public:
	Game();
	void run();
private:
	void processEvents();
	void update();
	void render();

	sf::RenderWindow m_window;
	GameState m_currState;
	MenuWindow m_menuWindow;
	GameWindow m_gameWindow;
	EndingWindow m_endingWindow;
};