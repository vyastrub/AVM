#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <vector>

class Avm
{

public:
	Avm() = default;
	Avm(const Avm &) = default;
	~Avm() = default;
	Avm & operator=(const Avm &) = default;

	std::string	get_status() const;
	void	read_file(char const* file_name);
	void	read_terminal();

	class Error: public std::exception
	{
	public:
		Error() = default;
		~Error() = default;
		Error(const Error &) = default;
		Error(std::string what);
		Error &		operator=(const Error &) = default;
		std::string	get_error() const;
		char const* what() const throw();
	
	private:
		std::string	_what;
	};

private:
	std::string _status_read;
};

std::ostream &	operator<<(std::ostream & os, Avm const & ref);
std::ostream &	operator<<(std::ostream & os, Avm::Error const & ref);
