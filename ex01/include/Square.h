#pragma once

#include <iostream>

class Square {
public:
	Square(const int width);
	void draw() const;
	void enlarge(const int n);
	void reduce(const int n);
private:
	int m_width;
};