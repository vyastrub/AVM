#include <climits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include "operand.hpp"
#include "definedFunctions.hpp"

Operand::Error::Error(std::string what)
{
	_what = what;
}

char const* Operand::Error::what() const throw()
{
	return _what.c_str();
}

IOperand* Operand::operator+( IOperand const & ref ) const
{
	OPERATION_PATTERN(+, std::stold(_value_str) + std::stold(ref.toString()))
}

IOperand* Operand::operator-( IOperand const & ref ) const
{
	OPERATION_PATTERN(-, std::stold(_value_str) - std::stold(ref.toString()))
}

IOperand* Operand::operator*( IOperand const & ref ) const
{
	OPERATION_PATTERN(*, std::stold(_value_str) * std::stold(ref.toString()))
}

IOperand* Operand::operator/( IOperand const & ref ) const
{
	if (std::stold(ref.toString()) == 0)
		throw Operand::Error("Div by zero!");

	OPERATION_PATTERN(/ , std::stold(_value_str) / std::stold(ref.toString()))
}

IOperand* Operand::operator%( IOperand const & ref ) const
{
	if (std::stold(ref.toString()) == 0)
		throw Operand::Error("Mod by zero!");
	
	OPERATION_PATTERN(%, fmod(std::stold(_value_str), std::stold(ref.toString())))
}

Operand::Operand(eOperandType type, std::string const & value) : _type{type}
{
	switch (_type)
	{
		case INT8:
		{
			FACTORY_FUNCTION(long, std::stoll, SCHAR_MIN, SCHAR_MAX, 0)
		}
		case INT16:
		{
			FACTORY_FUNCTION(long, std::stoll, SHRT_MIN, SHRT_MAX, 0)
		}
		case INT32:
		{
			FACTORY_FUNCTION(long, std::stoll, INT_MIN, INT_MAX, 0)
		}
		case FLOAT:
		{
			FACTORY_FUNCTION(double, std::stold, -FLT_MAX, FLT_MAX, FLT_DIG)
		}
		case DOUBLE:
		{
			FACTORY_FUNCTION(double, std::stold, -DBL_MAX, DBL_MAX, DBL_DIG)
		}
	}
}

int Operand::getPrecision() const
{
	return _precision;
}

eOperandType Operand::getType() const
{
	return _type;
}

std::string const &	Operand::toString() const
{
	return _value_str;	
}

std::ostream &	operator<<(std::ostream &os, Operand const & ref)
{
		os << ref.getType() << " : " << ref.toString() << " : " << ref.getPrecision();
		return os;
}

std::ostream &	operator<<(std::ostream &os, Operand::Error const & ref)
{
	os << ref.what();
	return os;
}
