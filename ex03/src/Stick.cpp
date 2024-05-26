#include "Stick.h"

// constructor
Stick::Stick(const sf::Vector2u& window_size, const int index)
{
	// set seed for random number
	srand((static_cast<unsigned int>(time(0)) + index) * index);

	// set stick spawn area
	unsigned int dis_from_boarder = 100;
	unsigned int spawn_area_x = window_size.x - dis_from_boarder;
	unsigned int spawn_area_y = window_size.y - dis_from_boarder;

	// set random position in given window size
	float x_pos = (float)getRandomNum(dis_from_boarder, spawn_area_x);
	float y_pos = (float)getRandomNum(dis_from_boarder, spawn_area_y);

	// set random angle for rotate : cannot be 90 degrees
	int rand_angle = 90;
	do {
		rand_angle = getRandomNum(0, 360);
	} while (rand_angle == 90 || rand_angle == 270);

	// create the SFML element
	m_shape.setSize(sf::Vector2f(200.0f, 10.0f));
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setPosition(x_pos, y_pos);
	m_shape.rotate((float)rand_angle);
}

// functions
void Stick::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

bool Stick::isClicked(const sf::Vector2i& mousePosition, sf::RenderWindow& window) const
{
	sf::FloatRect globalBounds = m_shape.getGlobalBounds();
	// Get the mouse position relative to the window
	sf::Vector2i mousePositionNew = sf::Mouse::getPosition(window);
	// Check if the mouse position is inside the global bounds of the rotated rectangle
	return globalBounds.contains(static_cast<sf::Vector2f>(mousePositionNew));
}

int Stick::getRandomNum(const int a, const int b)
{
	return a + (rand() % (b - a + 1));
}