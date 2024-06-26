#pragma once

#include <SFML/Graphics.hpp>

class EndingWindow {
public:
    EndingWindow(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    void draw();

    void setScore(const int score);
    void setEnding(const int ending);

    bool restartGameSelected() const;
    bool backToMenuSelected() const;

    void restartEnding();

private:
    sf::RenderWindow& m_window;

    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_score;
    sf::Text m_restartButton;
    sf::Text m_backButton;

    int m_gameEndState;

    bool m_restartSelected;
    bool m_backToMenuSelected;
};
