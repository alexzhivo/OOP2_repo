#pragma once

#include "Shape.h"

class Triangle : public Shape {
public:
	Triangle(const double width);

	void draw() const override;
	void enlarge(const int n) override;
	void reduce(const int n) override;
	std::string getName() const override;
private:
	double m_width;
};