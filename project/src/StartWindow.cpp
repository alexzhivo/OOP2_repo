#include "StartWindow.h"

StartWindow::StartWindow(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager)
    : Window(window,objectCreator,soundManager)
{
    m_wallpaper = objectCreator->getSprite("wallpaper");
    m_wallpaper.setScale(1.3f, 1.6f);
    m_title = objectCreator->getSprite("game_title");
    m_title.setPosition(25.f, 0.f);
    m_version = objectCreator->createText("v1.0.0", 10, "white", 1095.f, 335.f);
    m_subtext = objectCreator->createText(">> PRESS SPACE TO PLAY <<", 20, "white", 385.f, 650.f);
}

UserChoice StartWindow::handleInput(sf::Event& event)
{
    UserChoice choice;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            choice.isSelected = true;
            choice.nextWindow = WindowState::MENU;
            m_soundManager->playSound("select",false);
        }
    }
    return choice;
}

void StartWindow::update(float dt)
{
    m_wallpaper.move(100.f * dt, 0.f);
}

void StartWindow::render()
{
    runWallpaper();
	m_window.draw(m_title);
    m_window.draw(m_version);
    m_window.draw(m_subtext);
}

void StartWindow::runWallpaper()
{
    m_window.draw(m_wallpaper);
    m_wallpaper.move(-1276.f, 0.f);
    if (m_wallpaper.getPosition().x > 0) {
        m_wallpaper.move(-1276.f, 0.f);
    }
    m_window.draw(m_wallpaper);
    m_wallpaper.move(1276.f, 0.f);
}