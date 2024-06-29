#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class GameClock {
public:
	GameClock();

	int getMinutes() const;
	int getSeconds() const;
	bool isTimeZero() const;
	void addTime(int seconds);
	void initTime(int seconds);
	void stopTime();
	void startTime();

	std::string getTimeString();

private:
	sf::Clock m_clock;
	sf::Time m_time;
	bool m_isRunning;
};