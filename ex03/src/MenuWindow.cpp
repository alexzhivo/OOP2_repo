#include "MenuWindow.h"

MenuWindow::MenuWindow(sf::RenderWindow& window) : m_window(window), m_startSelected(false) {
    // Load font
    if (!m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        throw std::runtime_error("Failed to load font to MenuWindow.cpp");
    }

    // Configure title
    m_title.setFont(m_font);
    m_title.setString("Sticks");
    m_title.setCharacterSize(70);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(210, 180);

    // Configure play button
    m_playButton.setFont(m_font);
    m_playButton.setString("Play");
    m_playButton.setCharacterSize(30);
    m_playButton.setFillColor(sf::Color::White);
    m_playButton.setPosition(276, 380);

    // Configure exit button
    m_exitButton.setFont(m_font);
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(30);
    m_exitButton.setFillColor(sf::Color::White);
    m_exitButton.setPosition(280, 480);
}

void MenuWindow::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

            if (m_playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                m_startSelected = true;
            }
            else if (m_exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                m_window.close();
            }
        }
    }
}

void MenuWindow::update() {
    // Update menu items if needed
}

void MenuWindow::draw() {
    m_window.draw(m_title);
    m_window.draw(m_playButton);
    m_window.draw(m_exitButton);
}

bool MenuWindow::startGameSelected() const {
    return m_startSelected;
}

void MenuWindow::resetMenu() {
    m_startSelected = false;
}