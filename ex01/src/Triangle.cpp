#include "Triangle.h"

Triangle::Triangle(const int width)
	: m_width(width)
{}

void Triangle::draw() const
{
	for (int row = 0; row < m_width; row++) {
		for (int col = 0; col < m_width * 2 - 1; col++) {

			if (col == (m_width - 1) - row || col == (m_width - 1) + row) {
				std::cout << "*";
			}
			else if (row == m_width - 1) {
				if (col % 2 == 0) {
					std::cout << "*";
				}
				else {
					std::cout << " ";
				}
			}
			else {
				std::cout << " ";
			}

		}
		std::cout << "\n";
	}
}

void Triangle::enlarge(const int n)
{
	m_width *= n;
}

void Triangle::reduce(const int n)
{
	m_width /= n;
}

void Triangle::printName() const
{
	std::cout << "Triangle(" << m_width << ")";
}