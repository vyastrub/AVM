#include "avm.hpp"

int		main(int ac, char* av[])
{
	if (ac > 2)
	{
		std::cout << "Usage: ./avm or ./avm <file>" << std::endl;
		return 0;
	}
	Avm avm;
	try
	{
		if (ac == 2)
			avm.read_file(av[1]);
		else
			avm.read_terminal();
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}
