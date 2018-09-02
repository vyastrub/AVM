#pragma once
#include "session.hpp"

class Type
{
public:
	Type() = default;
	Type(Type const &ref) = default;
	~Type() = default;
	Type &	operator=(Type const &ref) = default;
				 
	std::string	 getType() const;
	eOperandType getEnumType() const;
	std::string	 getValue() const;			 
	void	setParam(std::string command);
	void	setType(std::string & type);
	void	setValue(std::string & value);
	 
	class Error: public std::exception
	{
	public:
		Error() = default;
		~Error() = default;
		Error(std::string what);
		Error(Error const &ref) = default;
		Error &		operator=(Error const &ref) = default;
		char const*	what() const throw();
	private:
		std::string	_what;
	};

private:
	std::string	_type;
	std::string	_value;

};

std::ostream &		operator<<(std::ostream & os, Type const & ref);
std::ostream &		operator<<(std::ostream & os, Type::Error const & ref);
