#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Ball.h"
#include "Brick.h"

class CollisionHandler {
public:
    void handleOutOfBoarder(std::list<std::shared_ptr<Ball>>& balls, sf::RectangleShape& platform, sf::RectangleShape& window);
    void handleBallPlatform(std::list<std::shared_ptr<Ball>>& balls, sf::RectangleShape& platform);
    bool handleBallBrick(std::list<std::shared_ptr<Ball>>& balls, std::vector<std::shared_ptr<Brick>>& bricks);
private:
    void keepBallInBoarder(std::shared_ptr<Ball>& ball, const sf::RectangleShape& rectangle);
    void keepPlatformInBoarder(sf::RectangleShape& platform, const sf::RectangleShape& rectangle);
    void resolveBallBrick(Ball& ball, Brick& brick);
};