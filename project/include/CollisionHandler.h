#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Ball.h"

class CollisionHandler {
public:
    void handleOutOfBoarder(std::list<std::unique_ptr<Ball>>& balls, sf::RectangleShape& window);
private:
    void keepBallInBoarder(std::unique_ptr<Ball>& ball, const sf::RectangleShape& rectangle);
};