#pragma once
#include <iostream>
#include <string>
#include <exception>

class Read
{

public:
	Read() = default;
	Read(const Read &) = default;
	~Read() = default;
	Read & operator=(const Read &) = default;
	std::string getStatus() const;
	void	readFromFile(char const* file_name);
	void	readFromTerminal();

	class Error: public std::exception
	{
	public:
		Error() = default;
		~Error() = default;
		Error(const Error &) = default;
		Error&	operator=(const Error &) = default;
		Error(std::string what);
		char const* what() const throw();
	private:
		std::string	_what;
	};

private:
	std::string _status_read;
};

std::ostream &	operator<<(std::ostream & os, Read const & ref);
std::ostream &	operator<<(std::ostream & os, Read::Error const & ref);
