#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectCreator.h"

#include <iostream> // TEST

enum class WindowState {
    START,
    MENU,
    PLAY,
    LEADERBOARD,
    HELP,
    SETTINGS,
    FINISH,
    EXIT,
    DEFAULT
};

struct UserChoice {
    bool isSelected = false;
    WindowState nextWindow = WindowState::DEFAULT;
};

class Window {
public:
    Window(sf::RenderWindow& window, ObjectCreator* objectCreator)
        : m_window(window), m_objectCreator(objectCreator) {};
    virtual ~Window() = default;

    virtual UserChoice handleInput(sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

protected:
    sf::RenderWindow& m_window;
    ObjectCreator* m_objectCreator;
};