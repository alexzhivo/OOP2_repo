#include "Stick.h"

#include <iostream> // TEST

constexpr double PI = 3.14159265359;

// constructor
Stick::Stick(const sf::Vector2u& window_size, const int index)
	: m_isUpperStick(true)
{
	// set the id of stick
	m_id = index;

	// set seed for random number
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(static_cast<unsigned int>(seed));

	// set stick spawn area
	unsigned int dis_from_boarder = 100;
	unsigned int spawn_area_x = window_size.x - dis_from_boarder;
	unsigned int spawn_area_y = window_size.y - dis_from_boarder;

	// set random position in given window size
	int x_pos = getRandomNum(dis_from_boarder, spawn_area_x);
	int y_pos = getRandomNum(dis_from_boarder, spawn_area_y);

	// set random angle for rotate : cannot be 90 degrees
	int rand_degree = 90;
	do {
		rand_degree = getRandomNum(0, 360);
	} while (rand_degree == 90 || rand_degree == 270);


	// create the SFML element
	m_shape.setSize(sf::Vector2f(LENGTH, THICKNESS));
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setPosition((float)x_pos, (float)y_pos);
	m_shape.rotate((float)rand_degree);

	m_points[0].m_x = x_pos;
	m_points[0].m_y = y_pos;
	m_points[1] = getEndPoint(m_points[0], LENGTH, rand_degree);

	// TEST TWO POINTS
	std::cout << "Point 1 :\n";
	std::cout << "x : " << m_points[0].m_x << std::endl;
	std::cout << "y : " << m_points[0].m_y << std::endl;
	std::cout << "Point 2 :\n";
	std::cout << "x : " << m_points[1].m_x << std::endl;
	std::cout << "y : " << m_points[1].m_y << std::endl;

}

// functions
void Stick::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

bool Stick::isClicked(const sf::Vector2i& mousePosition) const
{
	sf::FloatRect globalBounds = m_shape.getGlobalBounds();
	return globalBounds.contains(static_cast<sf::Vector2f>(mousePosition));
}

Point Stick::getPoint(int index) const
{
	if (index != 0 && index != 1) {
		std::cout << "bad index for Stick::getPoint()\n";
		exit(EXIT_FAILURE);
	}

	return { m_points[index].m_x , m_points[index].m_y };
}

void Stick::addIntersected(std::shared_ptr<Stick> stick)
{
	m_intersectedSticks.push_back(stick);
}

void Stick::removeIntersected(std::shared_ptr<Stick>& address)
{
	for (int i = 0; i < m_intersectedSticks.size(); i++) {
		if (m_intersectedSticks[i] == address) {
			m_intersectedSticks[i].reset();
			m_intersectedSticks.erase(m_intersectedSticks.begin() + i);
		}
	}
}

bool Stick::isUpperStick() const
{
	return m_isUpperStick;
}

void Stick::updateUpperStick()
{
	for (const auto& stick : m_intersectedSticks) {
		if (this->m_id < stick->getId()) {
			m_isUpperStick = false;
			return;
		}
	}
	m_isUpperStick = true;
}

int Stick::getRandomNum(const int a, const int b)
{
	return a + (rand() % (b - a + 1));
}

Point Stick::getEndPoint(const Point& startP, int length, int degree)
{
	// convert angle from degrees to radians
	double angleRad = degree * PI / 180.0;
	
	// calculate coordinates
	double new_x = startP.m_x + length * cos(angleRad);
	double new_y = startP.m_y + length * sin(angleRad);

	return { (int)new_x , (int)new_y };
}