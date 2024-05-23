#pragma once

#include <SFML/Graphics.hpp>

class GameWindow {
public:
	GameWindow(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event);
	void update();
	void draw();
	bool isGameOver() const;
	void restartGame();
	int getScore() const;

	void startClock();
	void stopClock();

	// TEST SCORE INCREASE
	bool isInsideWindow(const sf::Vector2i& point) const;

private:
	sf::RenderWindow& m_window;
	bool m_gameOver;
	int m_score;
	
	// text
	sf::Font m_font;
	sf::Text m_timerText;
	sf::Text m_scoreText;

	// clock
	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_gameDuration;
	bool m_clockRunning;

};