#pragma once

#include <SFML/Graphics.hpp>
#include <vector>	// for vector
#include <memory>	// for shared_ptr
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

	bool isInsideWindow(const sf::Vector2i& point) const;

	int getStickByClick(const sf::Vector2i& mousePosition);
	void pickUpStick(const int index);

private:
	sf::RenderWindow& m_window;
	int m_gameOver;	// on which state the game ended
	int m_score;
	int m_sticksPicked;
	int m_pickable;
	
	// text
	sf::Font m_font;
	sf::Text m_timerText;
	sf::Text m_scoreText;
	sf::Text m_sticksLeftText;
	sf::Text m_sticksPickedText;
	sf::Text m_pickableText;

	// clock
	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_gameDuration;
	bool m_clockRunning;

	// sticks
	const int m_numSticks;
	std::vector<std::shared_ptr<Stick>> m_sticks;

	void emptyAndFillSticks();
	void setPickable();
	int min(int a, int b);
	int max(int a, int b);
	bool onSegment(Point p, Point q, Point r);
	int orientation(Point p, Point q, Point r);
	bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};