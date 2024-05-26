#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Stick.h"

class GameWindow {
public:
	GameWindow(sf::RenderWindow& window, const int numSticks, const int time);
	void handleEvent(const sf::Event& event);
	void update();
	void draw();
	int isGameOver() const;
	void restartGame();
	int getScore() const;

	void startClock();
	void stopClock();

	// TEST SCORE INCREASE
	bool isInsideWindow(const sf::Vector2i& point) const;

	// TEST STICKS
	int getNumOfSticks() const {
		return (int)m_sticks.size();
	};
	int getStickByClick(const sf::Vector2i& mousePosition);
	void pickUpStick(const int index);

private:
	sf::RenderWindow& m_window;
	int m_gameOver;	// 0 - game not over , 1 - times up , 2 - no more sticks
	int m_score;
	int m_sticksPicked;
	
	// text
	sf::Font m_font;
	sf::Text m_timerText;
	sf::Text m_scoreText;
	sf::Text m_sticksLeftText;
	sf::Text m_sticksPickedText;

	// clock
	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_gameDuration;
	bool m_clockRunning;

	// sticks
	const int m_numSticks;
	std::vector<std::unique_ptr<Stick>> m_sticks;

	void emptyAndFillSticks();
};