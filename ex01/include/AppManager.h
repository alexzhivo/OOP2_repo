#pragma once

#include <iostream>
#include <vector>

#define BUFFSIZE 30

enum Command {
	CREATE, ENLARGE, REDUCE, DRAW,
	DUPLICATE, STACK, DELETE, HELP, EXIT, OTHER
};

class AppManager {
public:
	AppManager();
	~AppManager();
	void run();
	void insert(const int data);

	void print() const;
	void help() const;
private:
	Command getCommandValue(const char* cmd) const;

	std::vector<int> m_data;
};