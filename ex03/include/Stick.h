#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>
#include <chrono>
#include <random>

const int THICKNESS = 3,
			LENGTH = 180;

struct Point {
	int m_x;
	int m_y;
};

class Stick {
public:
	Stick(const sf::Vector2u& window_size, const int index);	// color and position

	void draw(sf::RenderWindow& window);
	bool isClicked(const sf::Vector2i& mousePosition) const;
	Point getPoint(int index) const;
	void addIntersected(std::shared_ptr<Stick> stick);
	void removeIntersected(std::shared_ptr<Stick>& address);
	bool isUpperStick() const;

	// TEST
	int getId() const {
		return m_id;
	}
	int getIntersectedNum() const {
		return (int)m_intersectedSticks.size();
	}
	void updateUpperStick();

	// for building the data structure
	bool operator<(const Stick& other) const {
		return this->m_id < other.m_id;
	}

private:
	sf::RectangleShape m_shape;
	Point m_points[2];
	
	// for building the data structure
	int m_id;
	bool m_isUpperStick;
	std::vector<std::shared_ptr<Stick>> m_intersectedSticks;
	
	int getRandomNum(const int a, const int b);	// utility function for creating random numbers
	Point getEndPoint(const Point& startP, int length, int degree);
};