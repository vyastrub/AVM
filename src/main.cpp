#include "avm.hpp"

int		main(int argc, char** argv)
{
	if (argc > 2)
		std::cout << "to much argument: use ./avm or ./avm <file>" << std::endl;
	else
	{
		try
		{
			Avm avm;
			if (argc == 2)
				avm.read_file((std::string)argv[1]);
			else
				avm.read_terminal();
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR: " << e.what() << std::endl;
		}
	}
	return (0);
}
