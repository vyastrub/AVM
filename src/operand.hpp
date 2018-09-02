#pragma once
#include <exception>
#include "IOperand.hpp"


class Operand : public IOperand
{

public:
	Operand() = default;
	~Operand() = default;
	Operand(Operand const &ref) = default;
	Operand& operator=(Operand const &ref) = default;
	Operand(eOperandType type, std::string const & value);
	
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
		Error&	operator=(Error const &ref);
		char const *	what() const throw();
	private:
		std::string	_what;
	};

private:
	std::string		_value_str;
	int				_precision;
	eOperandType	_type;

};

std::ostream &		operator<<(std::ostream & os, Operand const & ref);
std::ostream &		operator<<(std::ostream & os, Operand::Error const & ref);