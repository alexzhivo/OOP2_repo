#include "GameWindow.h"

#include <iostream>	// for save
#include <fstream>	// for save

GameWindow::GameWindow(sf::RenderWindow& window, const int numSticks, const int time)
	: m_window(window), m_gameOver(0), m_gameDuration(sf::seconds((float)time)),
	m_clockRunning(false), m_score(0), m_numSticks(numSticks), m_sticksPicked(0), 
	m_hintActive(0), m_saveIsClicked(false)
{
	try {
		if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
			throw std::runtime_error("Failed to load font to GameWindow.cpp");
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	// set number of sticks
	m_numSticks = getRandomNum(20, numSticks);

	// setting timer text
	m_timerText.setFont(m_font);
	m_timerText.setCharacterSize(20);
	m_timerText.setFillColor(sf::Color::White);
	m_timerText.setPosition(10, 10);

	// setting save button + text
	m_saveButton.setSize(sf::Vector2f(60, 30));
	m_saveButton.setFillColor(sf::Color::Black);
	m_saveButton.setOutlineThickness(2);
	m_saveButton.setOutlineColor(sf::Color::White);
	m_saveButton.setPosition(200, 10);

	m_saveText.setFont(m_font);
	m_saveText.setCharacterSize(20);
	m_saveText.setFillColor(sf::Color::White);
	m_saveText.setString("SAVE");
	m_saveText.setPosition(204, 13);

	// setting hint button + text
	m_hintButton.setSize(sf::Vector2f(60, 30));
	m_hintButton.setFillColor(sf::Color::Black);
	m_hintButton.setOutlineThickness(2);
	m_hintButton.setOutlineColor(sf::Color::White);
	m_hintButton.setPosition(330, 10);

	m_hintText.setFont(m_font);
	m_hintText.setCharacterSize(20);
	m_hintText.setFillColor(sf::Color::White);
	m_hintText.setString("HINT");
	m_hintText.setPosition(337, 13);

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
	m_loadedTime = m_timer.getElapsedTime();
}

void GameWindow::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
			auto floatPosition = sf::Vector2f((float)mousePosition.x, (float)mousePosition.y);
			if (isInsideWindow(mousePosition)) {

				if (handleSaveClick(mousePosition)) {
					return;
				}

				if (handleHintClick(mousePosition)) { // activate hint process
					return;
				}

				if (!m_hintActive) {	// cannot pickup sticks while in hint process
					int index = getStickByClick(floatPosition);
					if (index + 1 > 0) {
						pickUpStick(index);
					}
					if (index <= -2) {	// stick is not upper
						index = std::abs(index + 2);
						m_sticks[index]->flickerIntersected();
					}
				}
			}
		}
	}
}

bool GameWindow::isInsideWindow(const sf::Vector2i& point) const {
	sf::Vector2u windowSize = m_window.getSize();
	return point.x >= 0 && point.y >= 0 && point.x < static_cast<int>(windowSize.x) && point.y < static_cast<int>(windowSize.y);
}

bool GameWindow::handleHintClick(const sf::Vector2i& point) {
	sf::FloatRect globalBounds = m_hintButton.getGlobalBounds();
	if (globalBounds.contains(static_cast<sf::Vector2f>(point))) {

		// activate hint
		m_hintActive = 1;	// start hint process

		return true;
	}
	return false;
}

bool GameWindow::handleSaveClick(const sf::Vector2i& point) {
	sf::FloatRect globalBounds = m_saveButton.getGlobalBounds();
	if (globalBounds.contains(static_cast<sf::Vector2f>(point))) {

		// activate save
		
		// save the game to a file
		if (saveGame())	// checks if save finish correctly
			m_saveIsClicked = true;

		return true;
	}
	return false;
}

bool GameWindow::saveGame() const {
	const std::string filename = "gamesave.txt";

	try {
		std::ifstream infile(filename);
		if (infile.good()) {
			// File exists, rewrite it
			std::ofstream ofs(filename, std::ofstream::trunc);
			if (!ofs.is_open()) {
				throw "Failed to open the file for writing.";
			}
			writeOnFile(ofs);
			ofs.close();
		}
		else {
			// File does not exist, create it
			std::ofstream ofs(filename);
			if (!ofs.is_open()) {
				throw "Failed to create the file.";
			}
			writeOnFile(ofs);
			ofs.close();
		}
	}
	catch (const char* msg) {
		std::cerr << "Error: " << msg << std::endl;
		return false;
	}

	return true;
}


void GameWindow::writeOnFile(std::ofstream& ofs) const {
	if (ofs.is_open()) {
		ofs << m_score << std::endl;
		ofs << m_sticksPicked << std::endl;
		ofs << m_sticks.size() << std::endl;
		ofs << (int)m_elapsedTime.asSeconds() << std::endl;
		for (const auto& stick : m_sticks) {
			ofs << stick->getId() << " " 
				<< stick->getPos().x << " "
				<< stick->getPos().y << " "
				<< stick->getDegree() << " " 
				<< stick->getColorAsInt() << std::endl;
		}
	}
}

bool GameWindow::getSaveClick()
{
	if (m_saveIsClicked) {
		m_saveIsClicked = false;
		return true;
	}
	return false;
}

void GameWindow::processHint() {
	if (m_hintTimer.getElapsedTime().asSeconds() >= 0.7) {
		if (m_hintActive > 0 && m_pickableSticks.size() >= m_hintActive) {
			m_pickableSticks[m_hintActive - 1]->flicker();
			m_hintActive++;
			m_hintTimer.restart();
		}
		else {
			m_hintActive = 0; // finish hint process
		}
	}
}

// returns stick index in vector and if not clicked returns -1
int GameWindow::getStickByClick(const sf::Vector2f& mousePosition)
{
	for (int i = (int)m_sticks.size() - 1 ; i >= 0 ; i--) {
		if (m_sticks.at(i)->isClicked(mousePosition)) {
			if (m_sticks.at(i)->isUpperStick())
				return i;
			else {
				return -(i+2);
			}
		}
	}
	return -1;
}

void GameWindow::pickUpStick(const int index)
{
	// update values
	m_score += ((m_sticks[index]->getColorAsInt() + 1) * 2);
	m_sticksPicked++;

	// remove in intersected sticks
	for (auto& stick : m_sticks) {
		stick->removeIntersected(m_sticks[index]);
	}
	// remove the stick itself
	m_sticks[index].reset();
	m_sticks.erase(m_sticks.begin() + index);

	for (auto& stick : m_sticks) {
		stick->updateUpperStick();
	}
}

void GameWindow::update() {
	if (m_clockRunning) {
		// Update timer text
		m_elapsedTime = sf::seconds(m_timer.getElapsedTime().asSeconds() + m_loadedTime.asSeconds());
		sf::Time remainingTime = m_gameDuration - m_elapsedTime;
		int remainingSeconds = static_cast<int>(remainingTime.asSeconds());
		m_timerText.setString("Time : " + std::to_string(remainingSeconds));

		// Update score text
		m_scoreText.setString("Score : " + std::to_string(m_score));

		// Update pickable text
		setPickable();
		m_pickableText.setString("Pickable : " + std::to_string(m_pickableSticks.size()));

		// Update sticks left text
		m_sticksLeftText.setString("Sticks Left : " + std::to_string(m_sticks.size()));

		// Update sticks picked text
		m_sticksPickedText.setString("Picked : " + std::to_string(m_sticksPicked));

		// Check if the game is over
		if (m_elapsedTime >= m_gameDuration)
			m_gameOver = 1;

		if (m_sticksPicked == m_numSticks)
			m_gameOver = 2;
	
		processHint();
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
	// draw button
	m_window.draw(m_hintButton);
	m_window.draw(m_hintText);
	m_window.draw(m_saveButton);
	m_window.draw(m_saveText);

}

// returns 0 - if game not over, 1 - times up, 2 - no sticks left to pick up
int GameWindow::isGameOver() const {
	return m_gameOver;
}

void GameWindow::restartGame() {
	m_gameOver = 0;
	m_clockRunning = true;
	m_pickableSticks.clear();
	m_score = 0;
	m_sticksPicked = 0;
	emptyAndFillSticks();
	m_timer.restart();
	m_loadedTime = m_timer.getElapsedTime();
}

void GameWindow::loadGame() {
	m_pickableSticks.clear();
	if (!m_sticks.empty())
		m_sticks.clear();

	const std::string filename = "gamesave.txt";
	
	int numberOfSticks, time, id, pos_x, pos_y, degree, color;

	try {
		std::ifstream ifs(filename);
		if (!ifs.is_open()) {
			throw std::runtime_error("Failed to open the file for reading.");
		}


		ifs >> m_score >> m_sticksPicked >> numberOfSticks >> time;
		if (ifs.fail()) {
			throw std::runtime_error("Failed to read basic game data from file.");
		}

		for (int i = 0; i < numberOfSticks; i++) {
			ifs >> id >> pos_x >> pos_y >> degree >> color;
			if (ifs.fail()) {
				throw std::runtime_error("Failed to read stick data from file.");
			}

			m_sticks.push_back(std::make_shared<Stick>(m_window.getSize(), id));
			m_sticks[i]->setShape(pos_x, pos_y, degree);
			m_sticks[i]->setColor(color);
		}

		ifs.close();
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading game: " << e.what() << std::endl;
		return;
	}

	orderSticks();

	m_gameOver = 0;
	m_clockRunning = true;
	m_timer.restart();
	m_loadedTime = sf::seconds((float)time);
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

	orderSticks();
}

void GameWindow::orderSticks()
{
	// for each stick add all the intersected sticks
	for (int i = 0; i < m_sticks.size(); i++) {
		for (int j = 0; j < m_sticks.size(); j++) {
			if (i != j) {	// the same stick
				if (doIntersect(m_sticks[i]->getPoint(0), m_sticks[i]->getPoint(1),
					m_sticks[j]->getPoint(0), m_sticks[j]->getPoint(1))) {
					m_sticks[i]->addIntersected(m_sticks[j]);
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
	m_pickableSticks.clear();
	for (auto& stick : m_sticks) {
		if (stick->isUpperStick())
			m_pickableSticks.push_back(stick);
	}

	// sort vector by points (colors)
	std::sort(m_pickableSticks.begin(), m_pickableSticks.end(),
		[](std::shared_ptr<Stick>& a, std::shared_ptr<Stick>& b) 
	{
		return a->getColorAsInt() > b->getColorAsInt();
	});
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

int GameWindow::getRandomNum(const int a, const int b) const
{
	return a + (rand() % (b - a + 1));
}