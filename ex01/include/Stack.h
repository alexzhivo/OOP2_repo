#pragma once

#include "Shape.h"

class Stack : public Shape {
public:
	Stack(const std::shared_ptr<Shape>& s1,
		  const std::shared_ptr<Shape>& s2);

	void draw() const override;
	void enlarge(const int n) override;
	void reduce(const int n) override;
	std::string getName() const override;
private:
	std::shared_ptr<Shape> m_shapeTop;
	std::shared_ptr<Shape> m_shapeBottom;
};