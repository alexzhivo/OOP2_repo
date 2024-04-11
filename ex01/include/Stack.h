#pragma once

#include <iostream>
#include <memory>

class Stack {
public:
	Stack(const std::shared_ptr<Shape>& s1,const std::shared_ptr<Shape>& s2);

	void draw() const;
private:
	std::shared_ptr<Shape> m_shapeTop;
	std::shared_ptr<Shape> m_shapeBottom;
};