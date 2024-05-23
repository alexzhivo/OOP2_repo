#include "EndingWindow.h"

EndingWindow::EndingWindow(sf::RenderWindow& window) : m_window(window), 
    m_restartSelected(false), m_backToMenuSelected(false) {
    // Load font
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Handle error
        throw std::runtime_error("Failed to load font to EndingWindow.cpp");
    }

    // Configure title
    m_title.setFont(m_font);
    m_title.setString("Game Over");
    m_title.setCharacterSize(70);
    m_title.setFillColor(sf::Color::Red);
    m_title.setPosition(120, 180);

    // Configure score
    m_score.setFont(m_font);
    m_score.setCharacterSize(30);
    m_score.setFillColor(sf::Color::White);
    m_score.setPosition(230, 380);

    // Configure restart button
    m_restartButton.setFont(m_font);
    m_restartButton.setString("Restart");
    m_restartButton.setCharacterSize(30);
    m_restartButton.setFillColor(sf::Color::White);
    m_restartButton.setPosition(255, 480);

    // Configure exit button
    m_backButton.setFont(m_font);
    m_backButton.setString("Back To Menu");
    m_backButton.setCharacterSize(30);
    m_backButton.setFillColor(sf::Color::White);
    m_backButton.setPosition(210, 580);
}

void EndingWindow::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

            if (m_restartButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                m_restartSelected = true;
            }
            else if (m_backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                m_backToMenuSelected = true;
            }
        }
    }
}

void EndingWindow::update() {
    // Update menu items if needed
}

void EndingWindow::draw() {
    m_window.draw(m_title);
    m_window.draw(m_score);
    m_window.draw(m_restartButton);
    m_window.draw(m_backButton);
}

void EndingWindow::setScore(const int score) {
    m_score.setString("Score : " + std::to_string(score));
}

bool EndingWindow::restartGameSelected() const {
    return m_restartSelected;
}

bool EndingWindow::backToMenuSelected() const {
    return m_backToMenuSelected;
}

void EndingWindow::restartEnding() {
    m_restartSelected = false;
    m_backToMenuSelected = false;
}