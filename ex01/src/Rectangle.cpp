#include "Rectangle.h"

Rectangle::Rectangle(const int width, const int height)
	: m_width(width) , m_height(height)
{}

void Rectangle::draw() const
{
	for (int row = 0; row < m_height; row++) {
		for (int col = 0; col < (m_width * 2) - 1; col++) {
			if (col == 0 || col == (m_width * 2) - 2) {
				std::cout << "*";
			}
			else {
				if (row == 0 || row == m_height - 1) {
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

void Rectangle::enlarge(const int n)
{
	m_width *= n;
	m_height *= n;
}

void Rectangle::reduce(const int n)
{
	m_width /= n;
	m_height /= n;
}

void Rectangle::printName() const
{
	std::cout << "Rectangle(" << m_width << "," << m_height << ")";
}