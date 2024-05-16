#pragma once

#include "Validator.h"

template <typename T>
class RangeValidator : public Validator {
public:
	RangeValidator(const T& min, const T& max) : m_min(min) , m_max(max) {};
	~RangeValidator() {};

	bool validate(const int givenValue) const override {
		if (m_min <= givenValue && givenValue <= m_max)
			return true;
		return false;
	};

	bool validate(const Date& givenDate) const override { 
		if (m_min <= givenDate && givenDate <= m_max)
			return true;
		return false;
	};

	bool validate(const uint32_t) const override { return false; };		// not used.
	bool validate(const std::string&) const override { return false; };	// not used.

	std::string getMsg() const override {
		return m_msg;
	}
private:
	const T m_min;
	const T m_max;
	std::string m_msg = "Out of range.";
};