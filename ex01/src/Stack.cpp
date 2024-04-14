#include "Stack.h"

Stack::Stack(const std::shared_ptr<Shape>& s1, const std::shared_ptr<Shape>& s2)
	: m_shapeTop(s1), m_shapeBottom(s2) {}

void Stack::draw() const
{
	m_shapeTop->draw();
	m_shapeBottom->draw();
}

void Stack::enlarge(const int n)
{
	m_shapeTop->enlarge(n);
	m_shapeBottom->enlarge(n);
}

void Stack::reduce(const int n)
{
	m_shapeTop->reduce(n);
	m_shapeBottom->reduce(n);
}

std::string Stack::getName() const
{
	std::string name = "(" + m_shapeTop->getName() + ") / (" + m_shapeBottom->getName() + ")";
	return name;
}