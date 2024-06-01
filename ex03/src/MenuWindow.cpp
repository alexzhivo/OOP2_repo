#include "MenuWindow.h"

#include <iostream>

MenuWindow::MenuWindow(sf::RenderWindow& window) 
    : m_window(window), m_startSelected(false), m_loadSaveSelected(false)
{
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

    // Configure subtitle
    m_subtitle.setFont(m_font);
    m_subtitle.setString("by Alex Zhivotovsky");
    m_subtitle.setCharacterSize(12);
    m_subtitle.setFillColor(sf::Color::White);
    m_subtitle.setPosition(280, 255);

    // Configure play button
    m_playButton.setFont(m_font);
    m_playButton.setString("Play");
    m_playButton.setCharacterSize(30);
    m_playButton.setFillColor(sf::Color::White);
    m_playButton.setPosition(276, 380);

    // Configure loadsave button
    m_loadSaveButton.setFont(m_font);
    m_loadSaveButton.setString("Load Save");
    m_loadSaveButton.setCharacterSize(30);
    m_loadSaveButton.setPosition(235, 480);

    // Configure exit button
    m_exitButton.setFont(m_font);
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(30);
    m_exitButton.setFillColor(sf::Color::White);
    m_exitButton.setPosition(280, 580);
}

void MenuWindow::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            float x_pos = (float)sf::Mouse::getPosition(m_window).x;
            float y_pos = (float)sf::Mouse::getPosition(m_window).y;

            if (m_playButton.getGlobalBounds().contains(x_pos, y_pos)) {
                m_startSelected = true;
            }
            else if (m_loadSaveButton.getGlobalBounds().contains(x_pos, y_pos)) {
                m_loadSaveSelected = true;
            }
            else if (m_exitButton.getGlobalBounds().contains(x_pos, y_pos)) {
                m_window.close();
            }
        }
    }
}

void MenuWindow::update(const bool isGameSaved) {
    if (isGameSaved) {
        m_loadSaveButton.setFillColor(sf::Color::White);
    }
    else {
        m_loadSaveButton.setFillColor(sf::Color(50, 50, 50));
    }
}

void MenuWindow::draw() {
    m_window.draw(m_title);
    m_window.draw(m_subtitle);
    m_window.draw(m_playButton);
    m_window.draw(m_exitButton);
    m_window.draw(m_loadSaveButton);
}

bool MenuWindow::startGameSelected() {
    if (m_startSelected) {
        m_startSelected = false;
        return true;
    }
    return false;
}

bool MenuWindow::loadSaveSelected() {
    if (m_loadSaveSelected) {
        m_loadSaveSelected = false;
        return true;
    }
    return false;
}