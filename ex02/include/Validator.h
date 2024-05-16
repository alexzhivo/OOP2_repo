#pragma once

class Validator {
public:
	virtual ~Validator() = default;
	virtual bool validate(const std::string&) const = 0;
	virtual std::string getMsg() const = 0;
};