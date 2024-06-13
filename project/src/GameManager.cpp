#include "GameManager.h"

#include "iostream"                                         // TEST

// Constructors & Destructor

GameManager::GameManager() 
    : m_window(sf::VideoMode(1280, 920), "BrickBuster") 
{
    std::cout << "GameManager Constructor Activated.\n";    // TEST
};

GameManager::~GameManager()
{
    std::cout << "GameManager Destructor Activated.\n";     // TEST
};

// Public Class Functions

void GameManager::run() {

    sf::Clock clock;

    // Main game loop
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            handleInput(event);
        }

        // Calculate delta time
        sf::Time deltaTime = clock.restart();

        // Update the game state
        update(deltaTime.asSeconds());

        // Render the game state
        render();

    }
}


// Private Class Functions

void GameManager::handleInput(sf::Event& event) {
    
    // Handle Escape Press
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            m_window.close();
        }
    }

    // Handle Mouse Click
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
            std::cout << "Mouse Click (X,Y) : " << mousePosition.x <<           // TEST
                ", " << mousePosition.y << std::endl;
        }
    }
}

void GameManager::update(float deltaTime) {
    // Update game state
    // This is where game logic would be updated
}

void GameManager::render() {
    m_window.clear();

    // Render game objects
    // This is where drawing code would go

    m_window.display();
}