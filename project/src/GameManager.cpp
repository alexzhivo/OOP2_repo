#include "GameManager.h"

// Constructors & Destructor

GameManager::GameManager() 
    : m_window(sf::VideoMode(1280, 920), "BrickBuster"), m_currWindow(GameWindow::START)
{
	m_windows.push_back(std::make_unique<StartWindow>(m_window));
	m_windows.push_back(std::make_unique<MenuWindow>(m_window));
};

// Public Class Functions

void GameManager::run() {
	while (m_window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void GameManager::processEvents() {

	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();

		auto choice = m_windows[(int)m_currWindow]->handleInput(event);
		if (choice.isSelected) {
			m_currWindow = choice.nextWindow;
		}
	}
}

void GameManager::update() {

	m_windows[(int)m_currWindow]->update();

}

void GameManager::render() {

	m_window.clear();

	m_windows[(int)m_currWindow]->render();

	m_window.display();
}
