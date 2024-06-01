#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>
#include <chrono>
#include <random>

const int THICKNESS = 10,
			LENGTH = 180;

enum Color { Green , Blue , Orange , Red , Pink };

struct Point {
	int m_x;
	int m_y;
};

class Stick {
public:
	Stick(const sf::Vector2u& window_size, const int index);	// color and position

	void draw(sf::RenderWindow& window);
	void addIntersected(std::shared_ptr<Stick> stick);
	void removeIntersected(std::shared_ptr<Stick>& address);
	void updateUpperStick();
	void flickerIntersected();
	void flicker();
	
	// get
	int getId() const { return m_id; };
	sf::Vector2i getPos() const;
	int getDegree() const;
	bool isClicked(const sf::Vector2f& mousePosition) const;
	Point getPoint(int index) const;
	bool isUpperStick() const;
	int getColorAsInt() const;
	bool isFlickering() const { return m_isFlickering; };

	// set
	void setShape(const int x_pos, const int y_pos, const int rand_degree);
	void setColor(const int number);

	// operator overloading
	bool operator<(const Stick& other) const {
		return this->m_id < other.m_id;
	}

private:
	sf::RectangleShape m_shape;
	Point m_points[2];
	
	// effect flicker
	sf::Clock m_flickerClock;
	bool m_isFlickering;
	
	// data structure
	int m_id;
	bool m_isUpperStick;
	Color m_color;
	std::vector<std::shared_ptr<Stick>> m_intersectedSticks;
	
	// private functions
	int getRandomNum(const int a, const int b) const;	// utility function for creating random numbers
	Point getEndPoint(const Point& startP, int length, int degree) const;
};