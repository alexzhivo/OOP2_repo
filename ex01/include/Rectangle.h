#pragma once

#include <iostream>

class Rectangle {
public:
	Rectangle(const int width, const int height);
	void draw() const;
	void enlarge(const int n);
	void reduce(const int n);
	void printName() const;
private:
	int m_width;
	int m_height;
};