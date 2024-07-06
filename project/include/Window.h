#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectCreator.h"
#include "SoundManager.h"

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

#include <fstream>  // for files
#include <sstream>
#include <string>
#include <cctype>

#include <memory>   // for data
#include <list>

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
    Window(sf::RenderWindow& window, ObjectCreator* objectCreator, SoundManager* soundManager)
        : m_window(window), m_objectCreator(objectCreator) , m_soundManager(soundManager) {};
    virtual ~Window() = default;

    virtual UserChoice handleInput(sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

protected:
    sf::RenderWindow& m_window;
    ObjectCreator* m_objectCreator;
    SoundManager* m_soundManager;
};