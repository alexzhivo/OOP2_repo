#pragma once

#include <string>

template <typename T>
class ValuesToNames {
public:
	ValuesToNames() : m_values(T()) , m_option(0) {};
	~ValuesToNames() {};

	std::string valuesAndNames() const {
		std::string output = "(";
		for (int i = 0; i < m_values.getOptionNum(); i++) {
			output += m_values.getOption(i + 1);
			output += ", ";
		}
		output += ")\n";
		return output;
	}

	std::string getName() const {
		return m_values.getOption(m_option);
	}

	friend bool operator<=(const ValuesToNames<T>& leftSide, const ValuesToNames<T>& rightSide);
	friend std::ostream& operator<<(std::ostream& os, const ValuesToNames<T>& val);
	friend std::istream& operator>>(std::istream& is, ValuesToNames<T>& val);

private:
	T m_values;
	int m_option;
};

template <typename T>
bool operator<=(const ValuesToNames<T>& leftSide, const ValuesToNames<T>& rightSide) {
    return leftSide.m_option <= rightSide.m_option;
};
template <typename T>
std::ostream& operator<<(std::ostream& os, const ValuesToNames<T>& val) {
	os << val.getName();
    return os;
};
template <typename T>
std::istream& operator>>(std::istream& is, ValuesToNames<T>& val) {
	is >> val.m_option;
    return is;
};