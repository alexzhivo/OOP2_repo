#include "GameClock.h"

GameClock::GameClock() : m_isRunning(true) {}

int GameClock::getMinutes() const {
    int minutes = (int)(m_time.asSeconds() - m_clock.getElapsedTime().asSeconds());
    return minutes / 60;
}

int GameClock::getSeconds() const {
    int seconds = (int)(m_time.asSeconds() - m_clock.getElapsedTime().asSeconds());
    return seconds % 60;
}

bool GameClock::isTimeZero() const {
    return (m_time.asSeconds() - m_clock.getElapsedTime().asSeconds() <= 0);
}

void GameClock::addTime(int seconds) {
    m_time += sf::seconds(seconds);
}

void GameClock::initTime(int seconds) {
    m_time = sf::seconds(seconds);
    m_clock.restart();
    stopTime();
}

void GameClock::stopTime() {
    if (m_isRunning) {
        m_time -= m_clock.getElapsedTime();
        m_isRunning = false;
    }
    std::cout << "FROM STOPTIME() : Clock is : " << m_isRunning << '\n';
}

void GameClock::startTime() {
    if (!m_isRunning) {
        m_clock.restart();
        m_isRunning = true;
    }
    std::cout << "FROM STARTTIME() : Clock is : " << m_isRunning << '\n';
}

std::string GameClock::getTimeString()
{
    int minutes = getMinutes();
    int seconds = getSeconds();
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
    return std::string(buffer);
}