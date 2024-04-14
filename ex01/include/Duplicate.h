#pragma once

#include "Shape.h"

class Duplicate : public Shape {
public:
	Duplicate(const std::shared_ptr<Shape>& shape,const int amount);

	void draw() const override;
	void enlarge(const int n) override;
	void reduce(const int n) override;
	std::string getName() const override;
private:
	int m_amount;
	std::shared_ptr<Shape> m_shape;
};