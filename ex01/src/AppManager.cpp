#include "AppManager.h"

AppManager::AppManager()
	: m_data()
{
	std::cout << "successfuly created an App!\n";
}

AppManager::~AppManager()
{
	std::cout << "app has closed..\n";
}

void AppManager::run()
{
	std::string userInput;

	while (true)
	{
		print();

		std::getline(std::cin, userInput);

		Command cmd = getCommandValue(userInput);

		switch (cmd)
		{
		case CREATE:
			create(userInput);
			break;
		case ENLARGE:
			std::cout << "ENLARGE!\n";
			break;
		case REDUCE:
			std::cout << "REDUCE!\n";
			break;
		case DRAW:
			std::cout << "DRAW!\n";
			break;
		case DUPLICATE:
			std::cout << "DUPLICATE!\n";
			break;
		case STACK:
			std::cout << "STACK!\n";
			break;
		case DELETE:
			deleteCmd(userInput);
			break;
		case HELP: help(); break;
		case OTHER:
			std::cout << "not a valid command\n";
			break;
		case EXIT:
			std::cout << "Goodbye!\n";
			return;
		}
	}
}

Command AppManager::getCommandValue(const std::string& userInput) const
{
	size_t endOfFirstString = userInput.find(' ');
	std::string cmd = userInput.substr(0, endOfFirstString);

	if (cmd == "cre")
		return CREATE;
	else if (cmd == "en")
		return ENLARGE;
	else if (cmd == "red")
		return REDUCE;
	else if (cmd == "draw")
		return DRAW;
	else if (cmd == "dup")
		return DUPLICATE;
	else if (cmd == "stack")
		return STACK;
	else if (cmd == "del")
		return DELETE;
	else if (cmd == "help")
		return HELP;
	else if (cmd == "exit")
		return EXIT;
	else
		return OTHER;
}

// seperates the string into vector of strings
std::vector<std::string> AppManager::split(const std::string& str)
{
	std::vector<std::string> sepString;
	size_t start = 0, 
		   end = 0;

	while ((end = str.find(' ', start)) != std::string::npos)
	{
		sepString.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	sepString.push_back(str.substr(start));
	return sepString;
}

// function for create command
void AppManager::create(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 2 || args[1].size() == 0) {
		std::cout << "correct usage : cre <number>\n";
	}
	else {
		m_data.push_back(std::stoi(args[1]));
	}
}

void AppManager::print() const
{
	if (m_data.empty())
		std::cout << "Shape list is empty.\n";
	else
	{
		std::cout << "List of the available shapes :\n";
		for (int i = 0; i < m_data.size(); i++)
		{
			std::cout << i << ". (" << m_data.at(i) << ")\n";
		}
	}

	std::cout << "Enter command ('help' for the list of available commands): ";
}

void AppManager::deleteCmd(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 2 || args[1].size() == 0) {
		std::cout << "correct usage : del <number>\n";
	}
	else {
		int cell = std::stoi(args[1]);

		if (m_data.empty()) {
			std::cout << "list is empty, nothing to delete.\n";
			return;
		} 
		if (m_data.size() < cell + 1 || cell < 0) {
			std::cout << "number is not in range of the list!\n";
			return;
		}
		m_data.erase(m_data.begin() + cell);
	}
}

void AppManager::help() const
{
	std::cout << "The available commands are :\n"
		<< "* cre(ate shape) < t - triangle | r - rectangle | s - square > x[y] -\n"
		<< "  create new shape according to the chosen letter, with the given\n "
		<< "  size(s) (y must be given only for a rectangle)\n"
		<< "* en(large) num n - enlarge the size of the sides of shape #num by n (1 - 10)\n"
		<< "* red(uce) num n - reduce the size of the sides of shape #num by n (1 - 10)\n"
		<< "* draw num - draw shape #num\n"
		<< "* dup(licate) num n - create a new shape which is a n times\n"
		<< "  (vertical)duplication of shape #num\n"
		<< "* stack num1 num2 - create a new shape by stacking shape number #num1\n"
		<< "  over shape number #num2\n"
		<< "* del(ete) num - delete shape #num from the shape list\n"
		<< "* help - print this command list\n"
		<< "* exit - exit the program\n";
}