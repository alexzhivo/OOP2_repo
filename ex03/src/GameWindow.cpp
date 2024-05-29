#include "GameWindow.h"

#include <iostream> // TEST

GameWindow::GameWindow(sf::RenderWindow& window, const int numSticks, const int time)
	: m_window(window), m_gameOver(0), m_gameDuration(sf::seconds((float)time)),
	m_clockRunning(false), m_score(0), m_numSticks(numSticks), m_sticksPicked(0), m_pickable(0)
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
	m_scoreText.setPosition(485, 10);

	// setting sticks left text
	m_sticksLeftText.setFont(m_font);
	m_sticksLeftText.setCharacterSize(20);
	m_sticksLeftText.setFillColor(sf::Color::White);
	m_sticksLeftText.setPosition(10, 770);

	// setting pickable text
	m_pickableText.setFont(m_font);
	m_pickableText.setCharacterSize(20);
	m_pickableText.setFillColor(sf::Color::White);
	m_pickableText.setPosition(250, 770);

	// setting sticks picked text
	m_sticksPickedText.setFont(m_font);
	m_sticksPickedText.setCharacterSize(20);
	m_sticksPickedText.setFillColor(sf::Color::White);
	m_sticksPickedText.setPosition(485, 770);

	m_timer.restart();
}

void GameWindow::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
			if (isInsideWindow(mousePosition)) {
				
				// TEST
				std::cout << "MouseClick : " << mousePosition.x << " " << mousePosition.y << std::endl;
				for (const auto& stick : m_sticks) {
					std::cout << stick->getId() << " stick has intersected : " << stick->getIntersectedNum() << ", is upper : " << stick->isUpperStick() << std::endl;
				}

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
		if (m_sticks.at(i)->isClicked(mousePosition) && m_sticks.at(i)->isUpperStick()) {
			return i;
		}
	}
	return -1;
}

void GameWindow::pickUpStick(const int index)
{
	// remove in intersected sticks
	for (auto& stick : m_sticks) {
		stick->removeIntersected(m_sticks[index]);
	}
	// remove the stick itself
	m_sticks[index].reset();
	m_sticks.erase(m_sticks.begin() + index);

	// update values
	m_score += 5;
	m_sticksPicked++;
	for (auto& stick : m_sticks) {
		stick->updateUpperStick();
	}
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

		// Update pickable text
		setPickable();
		m_pickableText.setString("Pickable : " + std::to_string(m_pickable));

		// Update sticks left text
		m_sticksLeftText.setString("Sticks Left : " + std::to_string(m_sticks.size()));

		// Update sticks picked text
		m_sticksPickedText.setString("Picked : " + std::to_string(m_sticksPicked));

		// Check if the game is over
		if (elapsedTime >= m_gameDuration) {
			m_gameOver = 1;
		}

		if (m_sticksPicked == m_numSticks)
			m_gameOver = 2;
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
	m_window.draw(m_pickableText);
	m_window.draw(m_sticksPickedText);
	m_window.draw(m_scoreText);

}

// returns 0 - if game not over, 1 - times up, 2 - no sticks left to pick up
int GameWindow::isGameOver() const {
	return m_gameOver;
}

void GameWindow::restartGame() {
	m_gameOver = 0;
	m_clockRunning = true;
	m_pickable = 0;
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
		m_sticks.push_back(std::make_shared<Stick>(m_window.getSize(), i));

	// for each stick add all the intersected sticks
	for (int i = 0; i < m_numSticks; i++) {
		for (int j = 0; j < m_numSticks; j++) {
			if (i != j) {	// the same stick
				if (doIntersect(m_sticks[i]->getPoint(0), m_sticks[i]->getPoint(1),
								m_sticks[j]->getPoint(0), m_sticks[j]->getPoint(1))) {
					m_sticks[i]->addIntersected(m_sticks[j]);	
					std::cout << "Sticks Intersected!\n";
				}
			}
		}
	}

	// update upper sticks
	for (auto& stick : m_sticks) {
		stick->updateUpperStick();
	}

}

void GameWindow::setPickable()
{
	int counter = 0;
	for (const auto& stick : m_sticks) {
		if (stick->isUpperStick())
			counter++;
	}
	m_pickable = counter;
}

// utility function for checking if two lines Intersect

// min and max functions
int GameWindow::min(int a, int b) {
	return (a < b) ? a : b;
}

int GameWindow::max(int a, int b) {
	return (a > b) ? a : b;
}

// Given three collinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool GameWindow::onSegment(Point p, Point q, Point r)
{
	if (q.m_x <= max(p.m_x, r.m_x) && q.m_x >= min(p.m_x, r.m_x) &&
		q.m_y <= max(p.m_y, r.m_y) && q.m_y >= min(p.m_y, r.m_y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int GameWindow::orientation(Point p, Point q, Point r)
{
	int val = (q.m_y - p.m_y) * (r.m_x - q.m_x) -
		(q.m_x - p.m_x) * (r.m_y - q.m_y);

	if (val == 0) return 0;  // collinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool GameWindow::doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}