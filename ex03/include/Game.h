#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "MenuWindow.h"
#include "GameWindow.h"
#include "EndingWindow.h"

const unsigned int WINDOW_WIDTH = 600,
				   WINDOW_HEIGTH = 800,
				   NUM_OF_STICKS = 5,
				   GAME_TIME = 60;

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