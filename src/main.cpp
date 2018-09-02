#include "read.hpp"

int		main(int ac, char* av[])
{
	if (ac > 2)
	{
		std::cout << "Usage: ./avm or ./avm <file>" << std::endl;
		return 0;
	}
	Read avm;
	try
	{
		if (ac == 2)
			avm.readFromFile(av[1]);
		else
			avm.readFromTerminal();
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}
