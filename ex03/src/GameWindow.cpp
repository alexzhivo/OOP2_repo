#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window, const int numSticks)
	: m_window(window), m_gameOver(false), m_gameDuration(sf::seconds(5)),
	m_clockRunning(false), m_score(0), m_numSticks(numSticks)
{
	if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
		throw std::runtime_error("Failed to load font to GameWindow.cpp");
	}

	// setting timer text
	m_timerText.setFont(m_font);
	m_timerText.setCharacterSize(20);
	m_timerText.setFillColor(sf::Color::White);
	m_timerText.setPosition(10, 10);

	// setting score text
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(20);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(490, 10);

	m_timer.restart();
}

void GameWindow::handleEvent(const sf::Event& event) {
	// TEST SCORE INCREASE
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
			if (isInsideWindow(mousePosition)) {
				m_score += 5;
			}
		}
	}
}

// TEST SCORE INCREASE
bool GameWindow::isInsideWindow(const sf::Vector2i& point) const {
	sf::Vector2u windowSize = m_window.getSize();
	return point.x >= 0 && point.y >= 0 && point.x < static_cast<int>(windowSize.x) && point.y < static_cast<int>(windowSize.y);
}

void GameWindow::update() {
	if (m_clockRunning) {
		// Update timer text
		sf::Time elapsedTime = m_timer.getElapsedTime();
		sf::Time remainingTime = m_gameDuration - elapsedTime;
		int remainingSeconds = static_cast<int>(remainingTime.asSeconds());
		m_timerText.setString("Time Remaining: " + std::to_string(remainingSeconds));

		// Update score text
		m_scoreText.setString("Score : " + std::to_string(m_score));

		// Check if the game is over
		if (elapsedTime >= m_gameDuration) {
			m_gameOver = true;
		}
	}
}

void GameWindow::draw() {

	// draw all sticks 
	for (const auto& stick : m_sticks) {
		stick->draw(m_window);
	}
	// draw text
	m_window.draw(m_timerText);
	m_window.draw(m_scoreText);

}

bool GameWindow::isGameOver() const {
	return m_gameOver;
}

void GameWindow::restartGame() {
	m_gameOver = false;
	m_clockRunning = true;
	m_score = 0;
	emptyAndFillSticks();
	m_timer.restart();
}

int GameWindow::getScore() const {
	return m_score;
}

void GameWindow::startClock() {
	if(!m_clockRunning)
		m_timer.restart(); // Start the clock
	m_clockRunning = true; // Set the flag to indicate that the clock is running
}

void GameWindow::stopClock() {
	m_clockRunning = false; // Set the flag to indicate that the clock is stopped
}

// private functions
void GameWindow::emptyAndFillSticks()
{
	// clear sticks
	if (!m_sticks.empty())
		m_sticks.clear();

	// add sticks
	for (int i = 0; i < m_numSticks; i++)
		m_sticks.push_back(std::make_unique<Stick>(m_window.getSize(),i));
}