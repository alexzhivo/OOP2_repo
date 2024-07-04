#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Ball.h"
#include "Brick.h"
#include "PowerUp.h"

enum class BrickCondition {
    NO_TOUCH,
    HIT,
    BREAK
};

struct BrickInfo {
    BrickCondition cond = BrickCondition::NO_TOUCH;
    float pos_x = 0;
    float pos_y = 0;
};

class CollisionHandler {
public:
    void handleOutOfBoarder(std::list<std::shared_ptr<Ball>>& balls, sf::RectangleShape& window);
    void handleBallPlatform(std::list<std::shared_ptr<Ball>>& balls, const sf::FloatRect& platform_rect);
    BrickInfo handleBallBrick(std::list<std::shared_ptr<Ball>>& balls, std::vector<std::shared_ptr<Brick>>& bricks);
    PowerType handlePowerPlatform(std::vector<std::shared_ptr<PowerUp>>& powers, const sf::FloatRect& platform_rect);
    void handlePowerUpWindow(std::vector<std::shared_ptr<PowerUp>>& powers, sf::RectangleShape& window);
    bool handlePlatformWindow(const sf::FloatRect& platform_rect, const sf::RectangleShape& window_shape);
private:
    bool keepBallInBoarder(std::shared_ptr<Ball>& ball, const sf::RectangleShape& rectangle);
    void keepPlatformInBoarder(sf::RectangleShape& platform, const sf::RectangleShape& rectangle);
    void resolveBallBrick(Ball& ball, Brick& brick);
};