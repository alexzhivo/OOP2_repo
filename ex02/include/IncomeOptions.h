#pragma once

#include <string>
#include <vector>

class IncomeOptions {
public:
	IncomeOptions() {
		m_options = { 
			"Monthly salary", 
			"Partial salary", 
			"Allowance", 
			"Scholarship" };
	}

	int getOptionNum() const {
		return (int)m_options.size();
	}

	std::string getOption(int index) const {
		if (index < 0 || index >= m_options.size()) {
			return std::to_string(index);
		}
		return std::to_string(index) + " - " + m_options[index];
	}

private:
	std::vector<std::string> m_options;
};