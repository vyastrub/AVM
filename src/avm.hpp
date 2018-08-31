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

	class 		Error: public std::exception
	{
	public:
		Error() = default;
		Error(std::string what);
		Error(const Error &) = default;
		~Error() = default;
		std::string				get_error() const;
		Error &					operator=(Error const &ref);

		char const *	what() const throw();
	
	private:
		std::string		_what;
	};

	void	read_file(std::string file_name);
	void	read_terminal();

private:
	std::string		_status_read;
};

std::ostream &		operator<<(std::ostream & os, Avm const & ref);
std::ostream &		operator<<(std::ostream & os, Avm::Error const & ref);
