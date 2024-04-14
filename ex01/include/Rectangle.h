#pragma once

#include "Shape.h"

class Rectangle : public Shape {
public:
	Rectangle(const double width, const double height);

	void draw() const override;
	void enlarge(const int n) override;
	void reduce(const int n) override;
	std::string getName() const override;
private:
	double m_width;
	double m_height;
};