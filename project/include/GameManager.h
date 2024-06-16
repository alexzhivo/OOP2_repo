#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "iostream"              // TEST

#include "Window.h"
#include "StartWindow.h"
#include "MenuWindow.h"

class GameManager {
public:
    GameManager();

    void run();
private:
    sf::RenderWindow m_window;
    GameWindow m_currWindow;

    std::vector<std::unique_ptr<Window>> m_windows;

    // functions
    void processEvents();
    void update();
    void render();
};