#include "GameManager.h"

// Constructors & Destructor

GameManager::GameManager() 
    : m_window(sf::VideoMode(1280, 920), "BrickBuster"), m_currWindow(WindowState::START)
{
	// Creating the Window Vector
	m_windows.push_back(std::make_unique<StartWindow>(m_window, &m_objectCreator, &m_soundManager));
	m_windows.push_back(std::make_unique<MenuWindow>(m_window, &m_objectCreator, &m_soundManager));
	m_windows.push_back(std::make_unique<GameWindow>(m_window, &m_objectCreator, &m_soundManager));
	m_windows.push_back(std::make_unique<LeaderboardWindow>(m_window, &m_objectCreator, &m_soundManager));
	m_windows.push_back(std::make_unique<HelpWindow>(m_window, &m_objectCreator, &m_soundManager));
	m_windows.push_back(std::make_unique<SettingsWindow>(m_window, &m_objectCreator, &m_soundManager));
	m_windows.push_back(std::make_unique<FinishWindow>(m_window, &m_objectCreator, &m_soundManager));

	// Set Framerate for Game
	m_window.setFramerateLimit(60);
};

//	Main Game Loop : process -> update -> render.
void GameManager::run() 
{
	m_soundManager.playSound("theme_music", true);

	sf::Clock clock;		// main game clock for delta-time
	//sf::Clock fps_clock;	// (for fps count)

	while (m_window.isOpen()) {
		// (for fps count) print fps to terminal
		//std::cout << "fps: " << getFPS(fps_clock) << '\n';

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
			else {
				if (choice.nextWindow == WindowState::PLAY) {
					m_soundManager.stopSound("theme_music");
					m_soundManager.playSound("game_start", false);
					m_soundManager.playSound("game_music", true);
					updateAtGameStart();
				}
				if (choice.nextWindow == WindowState::MENU) {
					if (m_currWindow != WindowState::START)
						m_soundManager.playSound("theme_music", true);
					m_soundManager.stopSound("game_music");
				}
				m_currWindow = choice.nextWindow;
			}
		}
	}

	// waits for GameWindow to return Ended Signal
	if (m_currWindow == WindowState::PLAY) {

		GameWindow* gameWindow = dynamic_cast<GameWindow*>(m_windows[(int)WindowState::PLAY].get());
		FinishWindow* finishWindow = dynamic_cast<FinishWindow*>(m_windows[(int)WindowState::FINISH].get());
		SettingsWindow* settingsWindow = dynamic_cast<SettingsWindow*>(m_windows[(int)WindowState::SETTINGS].get());
		LeaderboardWindow* leaderboardWindow = dynamic_cast<LeaderboardWindow*>(m_windows[(int)WindowState::LEADERBOARD].get());

		GameState currGameState = gameWindow->getGameState();

		int finalScore;

		switch (currGameState) {
		case GameState::NEXT_LEVEL:
			gameWindow->setupNextLevel();
			break;
		case GameState::ENDED_WIN:
			finalScore = gameWindow->getScore();
			leaderboardWindow->insertValue(finalScore, settingsWindow->getPlayerName());
			finishWindow->setTitle("YOU WON!");
			finishWindow->setScore(finalScore);
			m_soundManager.playSound("game_win", false);
			break;
		case GameState::ENDED_TIME:
			finishWindow->setTitle("TIME IS UP..");
			m_soundManager.playSound("game_lose", false);
			break;
		case GameState::ENDED_LIVE:
			finishWindow->setTitle("Out Of Lives..");
			m_soundManager.playSound("game_lose", false);
			break;
		case GameState::NOT_ENDED:
			break;
		}

		if (currGameState != GameState::NOT_ENDED && currGameState != GameState::NEXT_LEVEL) 
		{
			m_soundManager.stopSound("game_music");
			gameWindow->reset();
			m_currWindow = WindowState::FINISH;
		}
	}
}

void GameManager::update(float dt)
{

	m_windows[(int)m_currWindow]->update(dt);

}

void GameManager::render() 
{
	m_window.clear(sf::Color(10, 60, 80));

	m_windows[(int)m_currWindow]->render();	// render current window used.

	m_window.display();
}

void GameManager::updateAtGameStart()
{
	GameWindow* gameWindow = dynamic_cast<GameWindow*>(m_windows[(int)WindowState::PLAY].get());
	LeaderboardWindow* leadWindow = dynamic_cast<LeaderboardWindow*>(m_windows[(int)WindowState::LEADERBOARD].get());
	
	// update Best Score text in-game
	gameWindow->updateBestScore(leadWindow->getBestScore());
}
// used for debug purpose and fps count
float GameManager::getFPS(sf::Clock& clock) const
{
	float currentTime = clock.restart().asSeconds();
	float fps = 1.0f / (currentTime);
	return fps;
}