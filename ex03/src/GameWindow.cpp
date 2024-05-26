#include "GameWindow.h"

GameWindow::GameWindow(sf::RenderWindow& window, const int numSticks, const int time)
	: m_window(window), m_gameOver(false), m_gameDuration(sf::seconds((float)time)),
	m_clockRunning(false), m_score(0), m_numSticks(numSticks), m_sticksPicked(0)
{
	if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
		throw std::runtime_error("Failed to load font to GameWindow.cpp");
	}

	// setting timer text
	m_timerText.setFont(m_font);
	m_timerText.setCharacterSize(20);
	m_timerText.setFillColor(sf::Color::White);
	m_timerText.setPosition(10, 10);

	// setting sticks left text
	m_sticksLeftText.setFont(m_font);
	m_sticksLeftText.setCharacterSize(20);
	m_sticksLeftText.setFillColor(sf::Color::White);
	m_sticksLeftText.setPosition(150, 10);

	// setting sticks picked text
	m_sticksPickedText.setFont(m_font);
	m_sticksPickedText.setCharacterSize(20);
	m_sticksPickedText.setFillColor(sf::Color::White);
	m_sticksPickedText.setPosition(300, 10);

	// setting score text
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(20);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(490, 10);

	m_timer.restart();
}

void GameWindow::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
			if (isInsideWindow(mousePosition)) {
				
				int index = getStickByClick(mousePosition);
				if (index + 1) {
					pickUpStick(index);
				}

			}
		}
	}
}

bool GameWindow::isInsideWindow(const sf::Vector2i& point) const {
	sf::Vector2u windowSize = m_window.getSize();
	return point.x >= 0 && point.y >= 0 && point.x < static_cast<int>(windowSize.x) && point.y < static_cast<int>(windowSize.y);
}

// returns stick index in vector and if not clicked returns -1
int GameWindow::getStickByClick(const sf::Vector2i& mousePosition)
{
	for (int i = 0; i < m_sticks.size(); i++) {
		if (m_sticks.at(i)->isClicked(mousePosition, m_window)) {
			return i;
		}
	}
	return -1;
}

void GameWindow::pickUpStick(const int index)
{
	m_sticks[index].reset();
	m_sticks.erase(m_sticks.begin() + index);
	m_score += 5;
	m_sticksPicked++;
}

void GameWindow::update() {
	if (m_clockRunning) {
		// Update timer text
		sf::Time elapsedTime = m_timer.getElapsedTime();
		sf::Time remainingTime = m_gameDuration - elapsedTime;
		int remainingSeconds = static_cast<int>(remainingTime.asSeconds());
		m_timerText.setString("Time : " + std::to_string(remainingSeconds));

		// Update score text
		m_scoreText.setString("Score : " + std::to_string(m_score));

		// Update sticks left text
		m_sticksLeftText.setString("Sticks Left : " + std::to_string(m_sticks.size()));

		// Update sticks picked text
		m_sticksPickedText.setString("Picked : " + std::to_string(m_sticksPicked));

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
	m_window.draw(m_sticksLeftText);
	m_window.draw(m_sticksPickedText);
	m_window.draw(m_scoreText);

}

bool GameWindow::isGameOver() const {
	return m_gameOver;
}

void GameWindow::restartGame() {
	m_gameOver = false;
	m_clockRunning = true;
	m_score = 0;
	m_sticksPicked = 0;
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