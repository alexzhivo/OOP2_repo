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
	void loadGame();
	int getScore() const;

	void startClock();
	void stopClock();

	int getStickByClick(const sf::Vector2f& mousePosition);
	void pickUpStick(const int index);

	bool getSaveClick();

private:
	sf::RenderWindow& m_window;
	int m_gameOver;	// on which state the game ended
	int m_score;
	
	// Info-Text
	sf::Font m_font;
	sf::Text m_timerText;
	sf::Text m_scoreText;
	sf::Text m_sticksLeftText;
	sf::Text m_sticksPickedText;
	sf::Text m_pickableText;

	// Hint Button
	sf::Text m_hintText;
	sf::RectangleShape m_hintButton;
	sf::Clock m_hintTimer;
	int m_hintActive; // what stick is hinting, 0 - if not active.

	// Save Button
	sf::Text m_saveText;
	sf::RectangleShape m_saveButton;
	bool m_saveIsClicked;

	// Timer
	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_loadedTime;
	sf::Time m_gameDuration;
	bool m_clockRunning;

	// Sticks
	const int m_numSticks;
	int m_sticksPicked;
	std::vector<std::shared_ptr<Stick>> m_sticks;
	std::vector<std::shared_ptr<Stick>> m_pickableSticks;

	// InClass Functions (SET/DO)
	void processHint();
	bool handleHintClick(const sf::Vector2i& point);
	bool handleSaveClick(const sf::Vector2i& point);
	void emptyAndFillSticks();
	void orderSticks();
	void setPickable();
	bool saveGame() const;
	void writeOnFile(std::ofstream& ofs) const;

	// InClass Functions (GET)
	bool isInsideWindow(const sf::Vector2i& point) const;
	int min(int a, int b);
	int max(int a, int b);
	bool onSegment(Point p, Point q, Point r);
	int orientation(Point p, Point q, Point r);
	bool doIntersect(Point p1, Point q1, Point p2, Point q2);
};