#include "GameManager.h"

// Constructors & Destructor

GameManager::GameManager() 
    : m_window(sf::VideoMode(1280, 920), "BrickBuster"), m_currWindow(WindowState::START)
{
	// Creating the Window Vector
	m_windows.push_back(std::make_unique<StartWindow>(m_window, &m_objectCreator));
	m_windows.push_back(std::make_unique<MenuWindow>(m_window, &m_objectCreator));
	m_windows.push_back(std::make_unique<GameWindow>(m_window, &m_objectCreator));
	m_windows.push_back(std::make_unique<LeaderboardWindow>(m_window, &m_objectCreator));
	m_windows.push_back(std::make_unique<HelpWindow>(m_window, &m_objectCreator));
	m_windows.push_back(std::make_unique<SettingsWindow>(m_window, &m_objectCreator));
	m_windows.push_back(std::make_unique<FinishWindow>(m_window, &m_objectCreator));

	// Set Framerate for Game
	m_window.setFramerateLimit(120);
};

//	Main Game Loop : process -> update -> render.
void GameManager::run() 
{

	sf::Clock clock;	// main game clock for delta-time
	
	while (m_window.isOpen()) {
		processEvents();
		float dt = clock.restart().asSeconds();
		update(dt);
		render();
	}
}

void GameManager::processEvents() 
{

	sf::Event event;
	
	// process user events
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();

		auto choice = m_windows[(int)m_currWindow]->handleInput(event);
		if (choice.isSelected) {
			if (choice.nextWindow == WindowState::EXIT)
				m_window.close();
			else
				m_currWindow = choice.nextWindow;
		}
	}

	// waits for GameWindow to return Ended Signal
	if (m_currWindow == WindowState::PLAY) {
		GameWindow* gameWindow = dynamic_cast<GameWindow*>(m_windows[(int)WindowState::PLAY].get());
		FinishWindow* finishWindow = dynamic_cast<FinishWindow*>(m_windows[(int)WindowState::FINISH].get());
		GameState currGameState = gameWindow->getGameState();
		int finalScore;

		switch (gameWindow->getGameState()) {
		case GameState::NOT_ENDED:
			break;
		case GameState::ENDED_WIN:
			finalScore = gameWindow->getScore();
			finishWindow->setScore(finalScore);
		case GameState::ENDED_TIME:
		default:
			gameWindow->resetWindow();
			m_currWindow = WindowState::FINISH;
			break;
		}
	}
}

void GameManager::update(float dt)
{

	m_windows[(int)m_currWindow]->update(dt);

}

void GameManager::render() 
{

	m_window.clear();

	m_windows[(int)m_currWindow]->render();	// render current window used.

	m_window.display();
}
