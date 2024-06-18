#include "GameManager.h"

// Constructors & Destructor

GameManager::GameManager() 
    : m_window(sf::VideoMode(1280, 920), "BrickBuster"), m_currWindow(WindowState::START)
{
	m_windows.push_back(std::make_unique<StartWindow>(m_window));
	m_windows.push_back(std::make_unique<MenuWindow>(m_window));
	m_windows.push_back(std::make_unique<GameWindow>(m_window));
	m_windows.push_back(std::make_unique<LeaderboardWindow>(m_window));
	m_windows.push_back(std::make_unique<HelpWindow>(m_window));
	m_windows.push_back(std::make_unique<SettingsWindow>(m_window));
	m_windows.push_back(std::make_unique<FinishWindow>(m_window));

	m_window.setFramerateLimit(120);
};

// Public Class Functions

void GameManager::run() {
	sf::Clock clock;
	while (m_window.isOpen()) {
		processEvents();
		float dt = clock.restart().asSeconds();
		update(dt);
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

void GameManager::update(float dt) {

	m_windows[(int)m_currWindow]->update(dt);

}

void GameManager::render() {

	m_window.clear();

	m_windows[(int)m_currWindow]->render();

	m_window.display();
}
