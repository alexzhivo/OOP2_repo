#pragma once

#include <SFML/Graphics.hpp>

class GameManager {
public:
    GameManager();
    ~GameManager();

    void run();

private:
    sf::RenderWindow m_window;

    void handleInput(sf::Event& event);
    void update(float deltaTime);
    void render();
};