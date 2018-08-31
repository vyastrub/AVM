#include "operand.hpp"
#include <climits>

#define OPERATION_PATTERN(operation)  													\
	eOperandType type;																	\
	if(_type >= ref.getType())															\
		type = _type;																	\
	else																				\
		type = ref.getType();															\
																						\
	int precision;																		\
	if (_precision >= ref.getPrecision())												\
		precision = _precision;															\
	else																				\
		precision = ref.getPrecision();													\
																						\
	switch (type)																		\
	{																					\
		case INT8:																		\
		{																				\
			auto result = std::stoll(_value_str) operation std::stoll(ref.toString());	\
			if (result < SCHAR_MIN)														\
				throw Operand::Error("Underflow name on a result");						\
			else if (result > SCHAR_MAX)												\
				throw Operand::Error("Overflow name on a result");						\
			std::stringstream ss (std::stringstream::out);								\
			ss << result;																\
			return (new Operand(INT8, ss.str()));										\
		}																				\
																						\
		case INT16:																		\
		{																				\
			auto result = std::stoll(_value_str) operation std::stoll(ref.toString());	\
			if (result < SHRT_MIN)														\
				throw Operand::Error("Underflow  name on a result"); 					\
			else if (result > SHRT_MAX)													\
				throw Operand::Error("Overflow name on a result");						\
			std::stringstream ss (std::stringstream::out);								\
			ss << result;																\
			return (new Operand(INT16, ss.str()));										\
		}																				\
																						\
		case INT32:																		\
		{																				\
			auto result = std::stoll(_value_str) operation std::stoll(ref.toString());	\
			if (result < INT_MIN)														\
				throw Operand::Error("Underflow name on a result");						\
			else if (result > INT_MAX)													\
				throw Operand::Error("Overflow name on a result");						\
			std::stringstream ss (std::stringstream::out);								\
			ss << result;																\
			return (new Operand(INT32, ss.str()));										\
		}																				\
																						\
		case FLOAT:																		\
		{																				\
			auto result = std::stold(_value_str) operation std::stold(ref.toString());	\
			if (result < -FLT_MIN)														\
				throw Operand::Error("Underflow name on a result");						\
			else if (result > FLT_MAX)													\
				throw Operand::Error("Overflow name on a result");						\
			std::stringstream ss (std::stringstream::out);								\
			ss << std::setprecision(precision) << result;								\
			return (new Operand(FLOAT, ss.str()));										\
		}																				\
																						\
		case DOUBLE:																	\
		{																				\
			auto result = std::stold(_value_str) operation std::stold(ref.toString());	\
			if (result < -DBL_MAX)														\
				throw Operand::Error("Underflow name on a result");						\
			else if (result > DBL_MAX)													\
				throw Operand::Error("Overflow name on a result");						\
			std::stringstream ss (std::stringstream::out);								\
			ss << std::setprecision(precision) << result;								\
			return (new Operand(DOUBLE, ss.str()));										\
		}																				\
	}																					\
	return nullptr;


#define FACTORY_FUNCTION(function, min, max, prec)			\
	bool		status = true;								\
	long long 	result;										\
	try														\
	{														\
		result = function(value);							\
	}														\
	catch (std::exception &e)								\
	{														\
		status = false;										\
		std::cout << "ERROR: " << e.what() << std::endl;	\
	}														\
	if (status == true)										\
	{														\
		if (result < min)									\
			throw Operand::Error("Underflow on a value");	\
		else if (result > max)								\
			throw Operand::Error("Overflow on a value");	\
		_precision = prec;									\
		std::stringstream ss(std::stringstream::out);		\
		ss << std::setprecision(_precision) << result;		\
		_value_str = ss.str();								\
	}														\
	else													\
		throw Operand::Error("Operand not found");

Operand::Error::Error(std::string what)
{
	_what = what;
}

std::string	Operand::Error::get_error() const
{
	return _what;
}

char const* Operand::Error::what() const throw()
{
	return _what.c_str();
}

IOperand *	Operand::operator+( IOperand const & ref ) const
{
	OPERATION_PATTERN(+)
}

IOperand *	Operand::operator-( IOperand const & ref ) const
{
	OPERATION_PATTERN(-)
}

IOperand *	Operand::operator*( IOperand const & ref ) const
{
	OPERATION_PATTERN(*)
}

IOperand *	Operand::operator/( IOperand const & ref ) const
{
	if (std::stold(ref.toString()) == 0)
		throw Operand::Error("Div by zero!");

	OPERATION_PATTERN(/)
}

IOperand *	Operand::operator%( IOperand const & ref ) const
{
	eOperandType type;
	if (_type >= ref.getType())
		type = _type;
	else
		type = ref.getType();

	int precision;
	if (_precision >= ref.getPrecision())
		precision = _precision;
	else
		precision = ref.getPrecision();

	if (std::stold(ref.toString()) == 0)
		throw Operand::Error("Mod by zero!");
	else
	{
		switch (type)
		{
			case INT8:
			{
				auto result = std::stoll(_value_str) % std::stoll(ref.toString());
				if (result < SCHAR_MIN)
					throw Operand::Error("Underflow mod on a result");
				else if (result > SCHAR_MAX)
					throw Operand::Error("Overflow mod on a result");
				std::stringstream ss (std::stringstream::out);
				ss << result;
				return (new Operand(INT8, ss.str()));
			}
			case INT16:
			{
				auto result = std::stoll(_value_str) % std::stoll(ref.toString());
				if (result < SHRT_MIN)
					throw Operand::Error("Underflow mod on a result");
				else if (result > SHRT_MAX)
					throw Operand::Error("Overflow mod on a result");
				std::stringstream ss (std::stringstream::out);
				ss << result;
				return (new Operand(INT16, ss.str()));
			}
			case INT32:
			{
				auto result = std::stoll(_value_str) % std::stoll(ref.toString());
				if (result < INT_MIN)
					throw Operand::Error("Underflow mod on a result");
				else if (result > INT_MAX)
					throw Operand::Error("Overflow mod on a result");
				std::stringstream ss (std::stringstream::out);
				ss << result;
				return (new Operand(INT32, ss.str()));
			}

			case FLOAT:
			{
				auto result = fmod(std::stold(_value_str), std::stold(ref.toString()));
				if (result < -FLT_MIN)
					throw Operand::Error("Underflow mod on a result");
				else if (result > FLT_MAX)
					throw Operand::Error("Overflow mod on a result");
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << result;
				return (new Operand(FLOAT, ss.str()));
			}		
			case DOUBLE:
			{
				auto result = fmod(std::stold(_value_str), std::stold(ref.toString()));
				if (result < -DBL_MAX)
					throw Operand::Error("Underflow mod on a result");
				else if (result > DBL_MAX)
					throw Operand::Error("Overflow mod on a result");
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << result;
				return (new Operand(DOUBLE, ss.str()));
			}
		}
	}
	return nullptr;
}



Operand::Operand(eOperandType type, std::string const & value) : _type{type}
{
	switch (_type)
	{
		case INT8:
		{
			FACTORY_FUNCTION(std::stoll, SCHAR_MIN, SCHAR_MAX, 0)
		}
		case INT16:
		{
			FACTORY_FUNCTION(std::stoll, SHRT_MIN, SHRT_MAX, 0)
		}
		case INT32:
		{
			FACTORY_FUNCTION(std::stoll, INT_MIN, INT_MAX, 0)
		}
		case FLOAT:
		{
			FACTORY_FUNCTION(std::stold, -FLT_MAX, FLT_MAX, FLT_DIG)
		}
		case DOUBLE:
		{
			FACTORY_FUNCTION(std::stold, -DBL_MAX, DBL_MAX, DBL_DIG)
		}
	}
}

int 			Operand::getPrecision() const
{
	return _precision;
}

eOperandType 	Operand::getType() const
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
	os << ref.get_error();
	return os;
}
