#pragma once

#include <SFML/Graphics.hpp>

enum class GameWindow {
    START,
    MENU,
    PLAY,
    FINISH,
    DEFAULT
};

struct UserChoice {
    bool isSelected = false;
    GameWindow nextWindow = GameWindow::DEFAULT;
};

class Window {
public:
    Window(sf::RenderWindow& window)
        : m_window(window) {};
    virtual ~Window() = default;

    virtual UserChoice handleInput(sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    sf::RenderWindow& m_window;
};