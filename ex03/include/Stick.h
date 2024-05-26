#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Stick {
public:
	Stick(const sf::Vector2u& window_size, const int index);	// color and position

	void draw(sf::RenderWindow& window);
	bool isClicked(const sf::Vector2i& mousePosition, sf::RenderWindow& window) const;
private:
	sf::RectangleShape m_shape;
	
	int getRandomNum(const int a, const int b);	// utility function for creating random numbers
};