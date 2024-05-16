#pragma once

#include <regex>

#include "Validator.h"

class RegexValidator : public Validator {
public:
	RegexValidator(const std::string& pattern) : m_pattern(pattern) {};
	~RegexValidator() {};

	bool validate(const std::string& value) const override {
		std::regex pattern(m_pattern);
		return std::regex_match(value, pattern);
	};

	std::string getMsg() const override {
		return m_msg;
	}
private:
	std::string m_pattern;
	std::string m_msg = "The input does not adhere to the expected format.";
};