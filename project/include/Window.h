#pragma once

#include <SFML/Graphics.hpp>

enum class WindowState {
    START,
    MENU,
    PLAY,
    LEADERBOARD,
    HELP,
    SETTINGS,
    EXIT,       // NEW ADDED TEST
    FINISH,
    DEFAULT
};

struct UserChoice {
    bool isSelected = false;
    WindowState nextWindow = WindowState::DEFAULT;
};

class Window {
public:
    Window(sf::RenderWindow& window)
        : m_window(window) {};
    virtual ~Window() = default;

    virtual UserChoice handleInput(sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

protected:
    sf::RenderWindow& m_window;
};