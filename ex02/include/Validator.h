#pragma once

#include <string>
#include "Date.h"

class Validator {
public:
	virtual ~Validator() = default;

	virtual bool validate(const std::string&) const = 0;
	virtual bool validate(const uint32_t) const = 0;
	virtual bool validate(const Date&) const = 0;

	virtual std::string getMsg() const = 0;
};