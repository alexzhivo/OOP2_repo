#pragma once

#include <iostream>
#include <string>
#include <memory>

class Validator;

class BaseField {
public:
	virtual ~BaseField() = default;
	virtual void ask() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool isValid() const = 0;
	virtual bool check() = 0;
	virtual void print(std::ostream& os) const = 0;

private:
};

template <typename T>
class Field : public BaseField {
public:
	Field(const std::string& text) : m_text(text), m_value(T()) , m_validator(nullptr) {};
	~Field() {};
	
	void addValidator(Validator* validator) {
		this->m_validator = validator;
	}

	void ask() override {
		std::cout << m_text << std::endl;
		std::cin >> m_value;
		m_empty = false;
	};

	bool isEmpty() const {
		return m_empty;
	};

	bool isValid() const {
		return m_valid;
	};

	bool check() {
		bool check = m_validator->validate(m_value);
		if (check)
			m_valid = true;
		return check;
	};

	void print(std::ostream& os) const override {
		os << "-------------------------------------------------------------------------\n";
		os << m_text << " = " << m_value;
		if (!m_valid) {
			os << " : " << m_validator->getMsg();
		}
		os << "\n";
		os << "-------------------------------------------------------------------------";
	}

private:
	const std::string m_text;
	T m_value;
	bool m_empty = true;
	bool m_valid = false;
	
	// validator
	Validator* m_validator;
};

std::ostream& operator<<(std::ostream& os, const BaseField& obj) {
	obj.print(os);
	return os;
}