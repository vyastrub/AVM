#include <fstream>
#include <vector>
#include <memory>
#include "read.hpp"
#include "session.hpp"

std::string Read::getStatus() const
{
	return _status_read;
}

Read::Error::Error(std::string what) : _what(what) {}

char const * Read::Error::what() const throw()
{
	return _what.c_str();
}

void 	Read::readFromFile(char const* file_name)
{
	std::ifstream	file(file_name, std::ios::in);
	std::string		command;
	size_t			number_error = 0;

	_status_read = "read_file";
	if (!file)
		throw Read::Error("File not found");
	std::unique_ptr<Session> VM(new Session());

	while (std::getline(file, command))
	{
		if (command.empty())
			continue;
		try
		{
			VM->run(std::move(command));
		}
		catch (std::exception &e)
		{
			number_error++;
			std::cout << "ERROR: " << e.what() << std::endl;
		}
	}
	file.close();
	if (number_error != 0)
		throw Read::Error("Session have " + std::to_string(number_error) + " errors");
}

void 		Read::readFromTerminal()
{
	std::unique_ptr<Session> VM(new Session());
	std::string		command;
	size_t			number_error = 0;

	_status_read = "read_terminal";
	while (getline(std::cin, command) && command.find(";;") != 0)
	{
		if (command.empty())
			continue;
		try
		{
			VM->run(std::move(command));
		}
		catch (std::exception &e)
		{
			number_error++;
			std::cout << "ERROR: " << e.what() << std::endl;
		}
	}
	if (number_error != 0)
		throw Read::Error("Session have " + std::to_string(number_error) + " errors");
}

std::ostream &			operator<<(std::ostream &os, Read const & ref)
{
		os << ref.getStatus();
		return os;
}

std::ostream &			operator<<(std::ostream &os, Read::Error const & ref)
{
	os << ref.what();
	return os;
}
