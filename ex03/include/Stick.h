#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Stick {
public:
	Stick(const sf::Vector2u& window_size, const int index);	// color and position

	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape m_shape; // SFML element
	
	int getRandomNum(const int a, const int b);	// utility function for creating random numbers
};