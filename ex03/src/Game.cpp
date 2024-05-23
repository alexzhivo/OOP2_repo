#include "Game.h"

#include <iostream> // TEST

Game::Game()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Sticks Game"), 
	m_currState(GameState::MainMenu),
	m_menuWindow(m_window), m_gameWindow(m_window), m_endingWindow(m_window)
{}

void Game::run() {
	while (m_window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();

		switch (m_currState) {
			case GameState::MainMenu:
				m_menuWindow.handleEvent(event);
				if (m_menuWindow.startGameSelected()) {
					m_gameWindow.restartGame();
					m_currState = GameState::Playing;
				}
				break;
			case GameState::Playing:
				m_gameWindow.handleEvent(event);
				if (m_gameWindow.isGameOver()) {
					m_currState = GameState::Ending;
				}
				break;
			case GameState::Ending:
				m_endingWindow.handleEvent(event);
				if (m_endingWindow.restartGameSelected()) {
					m_gameWindow.restartGame();
					m_endingWindow.restartEnding();
					m_currState = GameState::Playing;
				}
				else if (m_endingWindow.backToMenuSelected()) {
					m_endingWindow.restartEnding();
					m_menuWindow.resetMenu();
					m_currState = GameState::MainMenu;
				}
				break;
		}
	}
}

void Game::update() {
	switch (m_currState) {
		case GameState::MainMenu:
			m_menuWindow.update();
			break;
		case GameState::Playing:
			m_gameWindow.startClock();
			m_gameWindow.update();
			if (m_gameWindow.isGameOver()) {
				m_endingWindow.setScore(m_gameWindow.getScore());
				m_currState = GameState::Ending;
				m_gameWindow.stopClock();
			}
			break;
		case GameState::Ending:
			m_endingWindow.update();
			break;
	}
}

void Game::render() {
	m_window.clear();
	switch (m_currState) {
	case GameState::MainMenu:
		m_menuWindow.draw();
		break;
	case GameState::Playing:
		m_gameWindow.draw();
		break;
	case GameState::Ending:
		m_endingWindow.draw();
		break;
	}
	m_window.display();
}