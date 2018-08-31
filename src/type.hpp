#pragma once
#include "IOperand.hpp"
#include "machine.hpp"

class Type
{
public:
	Type() = default;
	Type(Type const &ref) = default;
	~Type() = default;
	Type &	operator=(Type const &ref) = default;
				 
	std::string	 get_type() const;
	eOperandType get_enum_type() const;
	std::string	 get_value() const;
				 
	void	set_param(std::string command);
	void	set_type(std::string & type);
	void	set_value(std::string & value);

	class 		Error: public std::exception
	{
	public:
		Error() = default;;
		Error(std::string what);
		 Error(Error const &ref) = default;
		 ~Error() = default;;
	
		std::string				get_error() const;
		Error &					operator=(Error const &ref) = default;
	
		char const *	what() const throw();
	
	private:
		std::string		_what;
	};

private:
	std::string		_type;
	std::string		_value;

};

std::ostream &		operator<<(std::ostream & os, Type const & ref);
std::ostream &		operator<<(std::ostream & os, Type::Error const & ref);
