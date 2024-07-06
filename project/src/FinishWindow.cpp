#include "FinishWindow.h"

FinishWindow::FinishWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager)
	: Window(window,objectCreator, soundManager)
{
    m_title = objectCreator->createTextButton("", 50, 'W', 250.f, 200.f);
    m_scoreText = objectCreator->createTextButton("", 50, 'W', 150.f, 300.f);
}

UserChoice FinishWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            choice.isSelected = true;
            choice.nextWindow = WindowState::MENU;
            resetWindow();
        }
    }
    return choice;
}

void FinishWindow::update(float dt)
{
    // >> UPDATE WINDOW
}

void FinishWindow::render()
{
    m_window.draw(m_title);
    m_window.draw(m_scoreText);
}

void FinishWindow::resetWindow()
{
    // >> RESET WINDOW
    m_scoreText.setString("");
}

void FinishWindow::setScore(int score)
{
    m_scoreText.setString("FINAL SCORE : " + std::to_string(score));
}

void FinishWindow::setTitle(std::string text)
{
    m_title.setString(text);
}