#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ObjectCreator.h"
#include "SoundManager.h"
#include "Window.h"
#include "StartWindow.h"
#include "MenuWindow.h"
#include "LeaderboardWindow.h"
#include "HelpWindow.h"
#include "SettingsWindow.h"
#include "GameWindow.h"
#include "FinishWindow.h"

class GameManager {
public:
    GameManager();

    void run();
private:
    sf::RenderWindow m_window;
    WindowState m_currWindow;
    ObjectCreator m_objectCreator;
    SoundManager m_soundManager;

    std::vector<std::unique_ptr<Window>> m_windows;

    // functions
    void processEvents();
    void update(float dt);
    void render();

    void updateAtGameStart();
    float getFPS(sf::Clock& clock) const;
};