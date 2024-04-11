#include "Stack.h"

Stack::Stack(const std::shared_ptr<Shape>& s1, const std::shared_ptr<Shape>& s2)
	: m_shapeTop(s1), m_shapeBottom(s2)
{}

Stack::draw() const
{
	m_shapeTop.draw();
	m_shapeBottom.draw();
}