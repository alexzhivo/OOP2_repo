#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Stack.h"
#include "Duplicate.h"
#include "Square.h"
#include "Triangle.h"
#include "Rectangle.h"

enum Command {
	CREATE, ENLARGE, REDUCE, DRAW,
	DUPLICATE, STACK, DELETE, HELP, EXIT, OTHER
};

class AppManager {
public:
	AppManager();
	~AppManager();
	void run();

private:
	void print() const;

	// user command functions
	void create(const std::string& userInput);
	void enlarge(const std::string& userInput);
	void reduce(const std::string& userInput);
	void draw(const std::string& userInput);
	void stack(const std::string& userInput);
	void duplicate(const std::string& userInput);
	void help() const;
	void deleteCmd(const std::string& userInput);

	// utility functions for getting input
	Command getCommandValue(const std::string& userInput) const;
	std::vector<std::string> split(const std::string& str);

	// members
	std::vector<std::shared_ptr<Shape>> m_shapes;
};