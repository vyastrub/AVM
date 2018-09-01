#include "avm.hpp"
#include "machine.hpp"

std::string	Avm::get_status() const
{
	return _status_read;
}

Avm::Error::Error(std::string what) : _what(what) {}

std::string	Avm::Error::get_error() const
{
	return _what;
}

char const * Avm::Error::what() const throw()
{
	return _what.c_str();
}

void 	Avm::read_file(char const* file_name)
{
	std::ifstream	file(file_name, std::ios::in);
	std::string		command;
	size_t			number_error = 0;

	_status_read = "read_file";
	if (file)
	{
		std::unique_ptr<Machine> VM(new Machine());

		while (std::getline(file, command))
		{
			if (!command.empty())
			{
				try
				{
					VM->run(command);
				}
				catch (std::exception &e)
				{
					number_error++;
					std::cout << "ERROR: " << e.what() << std::endl;
				}
			}
		}
		file.close();
		if (number_error != 0)
			throw Avm::Error("The assembly program includes " + std::to_string(number_error)
							 + " lexical or syntactic errors or input after exit");
	}
	else
		throw Avm::Error("File not found");
}

void 		Avm::read_terminal()
{
	std::unique_ptr<Machine> VM(new Machine());
	std::string		command;
	size_t			number_error = 0;

	_status_read = "read_terminal";
	while (getline(std::cin, command) && command.find(";;") != 0)
	{
		if (!command.empty())
		{
			try
			{
				VM->run(command);
			}
			catch (std::exception &e)
			{
				number_error++;
				std::cout << "ERROR: " << e.what() << std::endl;
			}
		}
	}
	if (number_error != 0)
		throw Avm::Error("The assembly program includes one or several lexical errors or syntactic errors or input after exit");
}

std::ostream &			operator<<(std::ostream &os, Avm const & ref)
{
		os << ref.get_status();
		return os;
}

std::ostream &			operator<<(std::ostream &os, Avm::Error const & ref)
{
	os << ref.get_error();
	return os;
}
