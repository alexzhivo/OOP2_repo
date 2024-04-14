#pragma once

#include "Shape.h"

class Square : public Shape {
public:
	Square(const double width);

	void draw() const override;
	void enlarge(const int n) override;
	void reduce(const int n) override;
	std::string getName() const override;
private:
	double m_width;
};