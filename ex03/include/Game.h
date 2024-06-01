#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "MenuWindow.h"
#include "GameWindow.h"
#include "EndingWindow.h"

const unsigned int WINDOW_WIDTH = 600,	// UNCHANGEABLE
				   WINDOW_HEIGTH = 800,	// UNCHANGEABLE
				   NUM_OF_STICKS = 100, // FOR MAX (min is 20)
				   GAME_TIME = 30; 

enum class GameState { Menu , Playing , Ending };

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

	void checkGameSave();

	sf::RenderWindow m_window;
	GameState m_currState;
	bool m_isGameSaved;

	MenuWindow m_menuWindow;
	GameWindow m_gameWindow;
	EndingWindow m_endingWindow;
};