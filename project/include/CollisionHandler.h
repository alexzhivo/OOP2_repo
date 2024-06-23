#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Ball.h"

class CollisionHandler {
public:
    void handleOutOfBoarder(std::list<std::unique_ptr<Ball>>& balls, sf::RectangleShape& platform, sf::RectangleShape& window);
    void handleBallPlatform(std::list<std::unique_ptr<Ball>>& balls, sf::RectangleShape& platform);
private:
    void keepBallInBoarder(std::unique_ptr<Ball>& ball, const sf::RectangleShape& rectangle);
    void keepPlatformInBoarder(sf::RectangleShape& platform, const sf::RectangleShape& rectangle);
};