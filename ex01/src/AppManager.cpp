#include "AppManager.h"

AppManager::AppManager()
	: m_shapes() {}

AppManager::~AppManager()
{
	m_shapes.clear();
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
			enlarge(userInput);
			break;
		case REDUCE:
			reduce(userInput);
			break;
		case DRAW:
			draw(userInput);
			break;
		case DUPLICATE:
			duplicate(userInput);
			break;
		case STACK:
			stack(userInput);
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

	if (args.size() != 3 && args.size() != 4) {
		std::cout << "correct usage : cre <type> <size>\n";
	}
	else {
		// check for valid input
		for (int i = 0; i < args.size(); i++) {
			if (args[i].size() == 0) {
				std::cout << "correct usage : cre <type> <size>\n";
				return;
			}
		}
		if (args[1] == "s" && args.size() == 3) {			// square create
			m_shapes.push_back(std::make_shared<Square>(std::stoi(args[2])));
		}
		else if (args[1] == "t" && args.size() == 3) {		// triangle create
			m_shapes.push_back(std::make_shared<Triangle>(std::stoi(args[2])));
		}
		else if (args[1] == "r" && args.size() == 4) {		// rectangle create
			m_shapes.push_back(std::make_shared<Rectangle>(std::stoi(args[2]), std::stoi(args[3])));
		}
		else {
			std::cout << "not valid option\n";
		}
	}
}

void AppManager::enlarge(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 3) {
		std::cout << "correct usage : en <index> <size>\n";
	}
	else {
		int index = stoi(args[1]);
		int size = stoi(args[2]);
		m_shapes.at(index)->enlarge(size);
	}
}

void AppManager::reduce(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 3) {
		std::cout << "correct usage : red <index> <size>\n";
	}
	else {
		int index = stoi(args[1]);
		int size = stoi(args[2]);
		m_shapes.at(index)->reduce(size);
	}
}

void AppManager::draw(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 2) {
		std::cout << "correct usage : draw <index>\n";
	}
	else {
		int index = stoi(args[1]);
		m_shapes.at(index)->draw();
	}
}

void AppManager::stack(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 3) {
		std::cout << "correct usage : stack <index> <index>\n";
	}
	else {
		int index1 = stoi(args[1]);
		int index2 = stoi(args[2]);
		m_shapes.push_back(std::make_shared<Stack>(m_shapes.at(index1), m_shapes.at(index2)));
	}
}

void AppManager::duplicate(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 3) {
		std::cout << "correct usage : dup <index> <number>\n";
	}
	else {
		int index = stoi(args[1]);
		int amount = stoi(args[2]);
		m_shapes.push_back(std::make_shared<Duplicate>(m_shapes.at(index),amount));
	}
}

void AppManager::print() const
{
	std::cout << std::endl;

	if (m_shapes.empty())
		std::cout << "Shape list is empty.\n";
	else
	{
		std::cout << "List of the available shapes :\n";
		for (int i = 0; i < m_shapes.size(); i++)
		{
			std::cout << i << ".  " << m_shapes.at(i)->getName() << "\n";
		}
	}
	
	std::cout << std::endl;

	std::cout << "Enter command ('help' for the list of available commands): ";
}

void AppManager::deleteCmd(const std::string& userInput)
{
	std::vector<std::string> args = split(userInput);

	if (args.size() != 2 ||
		args[1].size() == 0) {
		std::cout << "correct usage : del <index>\n";
	}
	else {
		int cell = std::stoi(args[1]);

		if (m_shapes.empty()) {
			std::cout << "list is empty, nothing to delete.\n";
			return;
		} 
		if (m_shapes.size() < cell + 1 || cell < 0) {
			std::cout << "index is not in range of the list!\n";
			return;
		}
		m_shapes.erase(m_shapes.begin() + cell);
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