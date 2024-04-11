#pragma once

#include <iostream>

class Square {
public:
	Square(const int width);
	void draw() const;
	void enlarge(const int n);
	void reduce(const int n);
	void printName() const;
private:
	int m_width;
};