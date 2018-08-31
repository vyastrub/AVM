#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <exception>
#include <math.h>
#include <float.h>
#include <memory>
#include "IOperand.hpp"

class Error;

class Operand : public IOperand
{

public:
	Operand() = default;
	Operand(Operand const &ref) = default;
	Operand(eOperandType type, std::string const & value);
	~Operand() = default;
	Operand &	operator=(Operand const &ref) = default;

	IOperand *	operator+(const IOperand & ref) const;
	IOperand *	operator-(const IOperand & ref) const;
	IOperand *	operator*(const IOperand & ref) const;
	IOperand *	operator/(const IOperand & ref) const;
	IOperand *	operator%(const IOperand & ref) const;

	int 				getPrecision() const;
	eOperandType		getType() const;
	std::string const &	toString() const;

	class 		Error: public std::exception
	{
	public:
		Error() = default;
		Error(std::string mesenge);
		Error(Error const &ref) = default;
		~Error() = default;

		std::string				get_error() const;
		Error &					operator=(Error const &ref);

		char const *	what() const throw();

	private:
		std::string		_what;
	};

private:
	std::string		_value_str;
	int				_precision;
	eOperandType	_type;

};

std::ostream &		operator<<(std::ostream & os, Operand const & ref);
std::ostream &		operator<<(std::ostream & os, Operand::Error const & ref);