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
	char buffer[BUFFSIZE];

	while (true)
	{
		print();

		std::cin >> buffer;
		Command cmd = getCommandValue(buffer);
		switch (cmd)
		{
		case CREATE:
			std::cout << "CREATE!\n";
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
			std::cout << "DELETE!\n";
			break;
		case HELP:
			help();	// prints the commands help screen
			break;
		case OTHER:
			std::cout << "not a valid command\n";
			break;
		case EXIT:
			return;
		}

		// clear buffer
		std::cin.clear();
		std::cin.ignore(BUFFSIZE, '\n');
	}
}

Command AppManager::getCommandValue(const char* cmd) const
{
	if (strcmp(cmd, "cre") == 0)
		return CREATE;
	else if (strcmp(cmd, "en") == 0)
		return ENLARGE;
	else if (strcmp(cmd, "red") == 0)
		return REDUCE;
	else if (strcmp(cmd, "draw") == 0)
		return DRAW;
	else if (strcmp(cmd, "dup") == 0)
		return DUPLICATE;
	else if (strcmp(cmd, "stack") == 0)
		return STACK;
	else if (strcmp(cmd, "del") == 0)
		return DELETE;
	else if (strcmp(cmd, "help") == 0)
		return HELP;
	else if (strcmp(cmd, "exit") == 0)
		return EXIT;
	else
		return OTHER;
}

void AppManager::insert(const int data)
{
	this->m_data.push_back(data);
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

void AppManager::help() const
{
	std::cout << "The available commands are :\n"
		<< "* cre(ate shape) < t - triangle | r - rectangle | s - square > x[y] -\n"
		<< "create new shape according to the chosen letter, with the given\n "
		<< "size(s) (y must be given only for a rectangle)\n"
		<< "* en(large) num n - enlarge the size of the sides of shape #num by n\n"
		<< "(1 - 10)\n"
		<< "* red(uce) num n - reduce the size of the sides of shape #num by n\n"
		<< "(1 - 10)\n"
		<< "* draw num - draw shape #num\n"
		<< "* dup(licate) num n - create a new shape which is a n times\n"
		<< "(vertical)duplication of shape #num\n"
		<< "* stack num1 num2 - create a new shape by stacking shape number #num1\n"
		<< "over shape number #num2\n"
		<< "* del(ete) num - delete shape #num from the shape list\n"
		<< "* help - print this command list\n"
		<< "* exit - exit the program\n";
}
