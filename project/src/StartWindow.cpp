#include "StartWindow.h"

StartWindow::StartWindow(sf::RenderWindow& window, ObjectCreator* objectCreator)
    : Window(window,objectCreator)
{
    m_title = objectCreator->createTextButton("BRICKBUSTER", 100, 'W', 300.f, 200.f);
    m_subtext = objectCreator->createTextButton("<< Press SPACE To Start >>", 20, 'G', 500.f, 700.f);
}

UserChoice StartWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            choice.isSelected = true;
            choice.nextWindow = WindowState::MENU;
        }
    }
    return choice;
}

void StartWindow::update(float dt)
{

}

void StartWindow::render()
{
	m_window.draw(m_title);
    m_window.draw(m_subtext);
}