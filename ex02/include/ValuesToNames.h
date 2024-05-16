#pragma once

template <typename T>
class ValuesToNames {
public:
	ValuesToNames() : m_options(T()) , m_choosenOption(0) {};
	~ValuesToNames() {};

	std::string valuesAndNames() {
		std::string output = "(1 - " +
			m_options.getOption(1) + ", 2 - " +
			m_options.getOption(2) + ", 3 - " +
			m_options.getOption(3) + ", 4 - " +
			m_options.getOption(4) + ")";
		return output;
	};

	std::string getDestName() const {
		return m_options.getOption(m_choosenOption);
	}

	friend std::ostream& operator<<(std::ostream& os, const ValuesToNames& val);
	friend std::istream& operator>>(std::istream& is, ValuesToNames& val);
	friend bool operator<=(const ValuesToNames& leftVal, const ValuesToNames& rightVal);

private:
	T m_options;
	int m_choosenOption;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ValuesToNames<T>& val) {
	os << val.getDestName();
	return os;
};

template <typename T>
std::istream& operator>>(std::istream& is, ValuesToNames<T>& val) {
	is >> val.m_choosenOption;
	return is;
};

template <typename T>
bool operator<=(const ValuesToNames<T>& leftVal, const ValuesToNames<T>& rightVal)
{
	return leftVal.m_choosenOption <= rightVal.m_choosenOption;
}