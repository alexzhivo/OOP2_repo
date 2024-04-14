#include "Duplicate.h"

Duplicate::Duplicate(const std::shared_ptr<Shape>& shape, const int amount)
	: m_shape(shape) , m_amount(amount) {}

void Duplicate::draw() const
{
	for (int i = 0; i < m_amount; i++) {
		m_shape->draw();
	}
}

void Duplicate::enlarge(const int n)
{
	m_shape->enlarge(n);
}

void Duplicate::reduce(const int n)
{
	m_shape->reduce(n);
}

std::string Duplicate::getName() const
{
	std::string name = std::to_string(m_amount) + " * (" + m_shape->getName() + ")";
	return name;
}