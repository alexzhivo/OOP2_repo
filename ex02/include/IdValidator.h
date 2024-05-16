#pragma once

#include "Validator.h"
#include <math.h>	// for sqrt() function

const int NUM_OF_DIGITS = 9;

class IdValidator : public Validator {
public:
	IdValidator() {};
	~IdValidator() {};

	bool validate(const uint32_t id) const override {
		uint32_t sum = 0;
		uint32_t temp;
		for (int i = 0; i < NUM_OF_DIGITS; i++) {
			temp = (id / (uint32_t)pow(10, (NUM_OF_DIGITS - (i + 1)))) % 10;
			if (i != NUM_OF_DIGITS - 1)
				temp *= ((i % 2) + 1);
			if (temp >= 10) {
				temp %= 9;
			}
			sum += temp;
		}
		return (sum % 10 == 0);
	};

	bool validate(const std::string&) const override { return false; };		// not used.
	bool validate(const Date&) const override { return false; };			// not used.
	bool validate(const int) const override { return false; };				// not used.

	std::string getMsg() const override {
		return m_msg;
	}
private:
	std::string m_msg = "Wrong control digit.";
};