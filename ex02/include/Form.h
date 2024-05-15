#pragma once

#include <memory>
#include <iostream>
#include <vector>

#include "Field.h"

class Form {
public:
	Form() : m_fields() {};
	~Form() {};

	template <typename T>
	void addField(Field<T>* field) {
		m_fields.push_back(field);
	};

	void fillForm() {
		for (int i = 0; i < m_fields.size(); i++) {
			if (m_fields[i]->isEmpty() || !m_fields[i]->isValid())
				m_fields[i]->ask();
		}
	};

	bool validateForm() const {
		bool passedValidation = true;
		for (int i = 0; i < m_fields.size(); i++) {
			if (!m_fields[i]->isValid()) {
				if (!m_fields[i]->check())
					passedValidation = false;

			}
		}
		return passedValidation;
	};

	friend std::ostream& operator<<(std::ostream& os, const Form& obj);

private:
	std::vector<BaseField*> m_fields;
};

std::ostream& operator<<(std::ostream& os, const Form& obj) {
	for (int i = 0; i < obj.m_fields.size(); i++) {
		os << *obj.m_fields[i] << std::endl;
	}
	return os;
}