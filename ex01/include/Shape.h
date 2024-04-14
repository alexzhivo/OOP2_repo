#pragma once

#include <iostream>
#include <string>
#include <memory>

class Shape {
public:
	virtual void draw() const = 0;
	virtual void enlarge(const int n) = 0;
	virtual void reduce(const int n) = 0;
	virtual std::string getName() const = 0;

	virtual ~Shape() {};
};