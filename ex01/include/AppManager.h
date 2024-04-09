#pragma once

#include <iostream>
#include <vector>
#include <string>

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
	// user command functions
	void create(const std::string& userInput);
	void print() const;
	void help() const;

	// utility functions for getting input
	Command getCommandValue(const std::string& userInput) const;
	std::vector<std::string> split(const std::string& str);

	// members
	std::vector<int> m_data;
};