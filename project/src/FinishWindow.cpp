#include "FinishWindow.h"

FinishWindow::FinishWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
	: Window(window,objectCreator)
{
    m_title = objectCreator->createTextButton("YOU WIN!", 100, 'W', 300.f, 200.f);
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
}

void FinishWindow::resetWindow()
{
    // >> RESET WINDOW
}