#include "Square.h"

Square::Square(const int width)
	: m_width(width)
{}

void Square::draw() const
{
	for (int row = 0; row < m_width; row++) {
		for (int col = 0; col < (m_width * 2) - 1; col++) {
			if (col == 0 || col == (m_width * 2) - 2) {
				std::cout << "*";
			}
			else {
				if (row == 0 || row == m_width - 1) {
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
		}
		std::cout << "\n";
	}
}

void Square::enlarge(const int n)
{
	m_width *= n;
}

void Square::reduce(const int n)
{
	m_width /= n;
}

void Square::printName() const
{
	std::cout << "Square(" << m_width << ")";
}