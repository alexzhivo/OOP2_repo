#pragma once

const int NUM_OF_OPTIONS = 4;

class IncomeOptions {
public:
	IncomeOptions() {};
	~IncomeOptions() {};

	std::string getOption(const int optionNum) const {
		if (optionNum > 0 && optionNum <= NUM_OF_OPTIONS)
			return m_incomes[optionNum - 1];
		return std::to_string(optionNum);
	}

private:
	std::string m_incomes[NUM_OF_OPTIONS] = {
		"Monthly salary",
		"Partial salary",
		"Allowance",
		"Scholarship"
	};
};