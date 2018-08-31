#include "operand.hpp"

/********************************************************************/

Operand::Error::Error(std::string what)
{
	_what = what;
}

std::string	Operand::Error::get_error() const
{
	return _what;
}

char const* Operand::Error::what() const
{
	return _what.c_str();
}

/********************************************************************/

IOperand *	Operand::operator+( IOperand const & ref ) const
{
	eOperandType type;
	if(_type >= ref.getType())
		type = _type;
	else
		type = ref.getType();

	int precision;
	if (_precision >= ref.getPrecision())
		precision = _precision;
	else
		precision = ref.getPrecision();

	switch (type)
	{
		case INT8:
		{
			auto rezult = std::stoll(_value_str) + std::stoll(ref.toString());
			if (rezult < SCHAR_MIN)
				throw Operand::Error("Underflow add on a rezult");
			else if (rezult > SCHAR_MAX)
				throw Operand::Error("Overflow add on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT8, ss.str()));
			}
		}
		break;
		
		case INT16:
		{
			auto rezult = std::stoll(_value_str) + std::stoll(ref.toString());
			if (rezult < SHRT_MIN)
				throw Operand::Error("Underflow add on a rezult");
			else if (rezult > SHRT_MAX)
				throw Operand::Error("Overflow add on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT16, ss.str()));
			}
		}
		break;

		case INT32:
		{
			auto rezult = std::stoll(_value_str) + std::stoll(ref.toString());
			if (rezult < INT_MIN)
				throw Operand::Error("Underflow add on a rezult");
			else if (rezult > INT_MAX)
				throw Operand::Error("Overflow add on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT32, ss.str()));
			}
		}
		break;

		case FLOAT:
		{
			auto rezult = std::stold(_value_str) + std::stold(ref.toString());
			if (rezult < -FLT_MIN)
				throw Operand::Error("Underflow add on a rezult");
			else if (rezult > FLT_MAX)
				throw Operand::Error("Overflow add on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << rezult;
				return (new Operand(FLOAT, ss.str()));
			}
		}
		break;
		
		case DOUBLE:
		{
			auto rezult = std::stold(_value_str) + std::stold(ref.toString());
			if (rezult < -DBL_MAX)
				throw Operand::Error("Underflow add on a rezult");
			else if (rezult > DBL_MAX)
				throw Operand::Error("Overflow add on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << rezult;
				return (new Operand(DOUBLE, ss.str()));
			}
		}
		break;
	}
	return nullptr;
}

IOperand *			Operand::operator-( IOperand const & ref ) const
{
	eOperandType type;
	if(_type >= ref.getType())
		type = _type;
	else
		type = ref.getType();

	int precision;
	if (_precision >= ref.getPrecision())
		precision = _precision;
	else
		precision = ref.getPrecision();


	switch (type)
	{
		case INT8:
		{
			auto rezult = std::stoll(_value_str) - std::stoll(ref.toString());
			if (rezult < SCHAR_MIN)
				throw Operand::Error("Underflow sub on a rezult");
			else if (rezult > SCHAR_MAX)
				throw Operand::Error("Overflow sub on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT8, ss.str()));
			}
		}
		break;
		
		case INT16:
		{
			auto rezult = std::stoll(_value_str) - std::stoll(ref.toString());
			if (rezult < SHRT_MIN)
				throw Operand::Error("Underflow sub on a rezult");
			else if (rezult > SHRT_MAX)
				throw Operand::Error("Overflow sub on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT16, ss.str()));
			}
		}
		break;

		case INT32:
		{
			auto rezult = std::stoll(_value_str) - std::stoll(ref.toString());
			if (rezult < INT_MIN)
				throw Operand::Error("Underflow sub on a rezult");
			else if (rezult > INT_MAX)
				throw Operand::Error("Overflow sub on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT32, ss.str()));
			}
		}
		break;

		case FLOAT:
		{
			auto rezult = std::stold(_value_str) - std::stold(ref.toString());
			if (rezult < -FLT_MIN)
				throw Operand::Error("Underflow sub on a rezult");
			else if (rezult > FLT_MAX)
				throw Operand::Error("Overflow sub on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << rezult;
				return (new Operand(FLOAT, ss.str()));
			}
		}
		break;
		
		case DOUBLE:
		{
			auto rezult = std::stold(_value_str) - std::stold(ref.toString());
			if (rezult < -DBL_MAX)
				throw Operand::Error("Underflow sub on a rezult");
			else if (rezult > DBL_MAX)
				throw Operand::Error("Overflow sub on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << rezult;
				return (new Operand(DOUBLE, ss.str()));
			}
		}
		break;
	}
	return nullptr;
}

IOperand *			Operand::operator*( IOperand const & ref ) const
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

	switch (type)
	{
		case INT8:
		{
			auto rezult = std::stoll(_value_str) * std::stoll(ref.toString());
			if (rezult < SCHAR_MIN)
				throw Operand::Error("Underflow mul on a rezult");
			else if (rezult > SCHAR_MAX)
				throw Operand::Error("Overflow mul on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT8, ss.str()));
			}
		}
		break;
		
		case INT16:
		{
			auto rezult = std::stoll(_value_str) * std::stoll(ref.toString());
			if (rezult < SHRT_MIN)
				throw Operand::Error("Underflow mul on a rezult");
			else if (rezult > SHRT_MAX)
				throw Operand::Error("Overflow mul on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT16, ss.str()));
			}
		}
		break;

		case INT32:
		{
			auto rezult = std::stoll(_value_str) * std::stoll(ref.toString());
			if (rezult < INT_MIN)
				throw Operand::Error("Underflow mul on a rezult");
			else if (rezult > INT_MAX)
				throw Operand::Error("Overflow mul on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << rezult;
				return (new Operand(INT32, ss.str()));
			}
		}
		break;

		case FLOAT:
		{
			auto rezult = std::stold(_value_str) * std::stold(ref.toString());
			if (rezult < -FLT_MIN)
				throw Operand::Error("Underflow mul on a rezult");
			else if (rezult > FLT_MAX)
				throw Operand::Error("Overflow mul on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << rezult;
				return (new Operand(FLOAT, ss.str()));
			}
		}
		break;
		
		case DOUBLE:
		{
			auto rezult = std::stold(_value_str) * std::stold(ref.toString());
			if (rezult < -DBL_MAX)
				throw Operand::Error("Underflow mul on a rezult");
			else if (rezult > DBL_MAX)
				throw Operand::Error("Overflow mul on a rezult");
			else
			{
				std::stringstream ss (std::stringstream::out);
				ss << std::setprecision(precision) << rezult;
				return (new Operand(DOUBLE, ss.str()));
			}
		}
		break;
	}
	return nullptr;
}

IOperand *			Operand::operator/( IOperand const & ref ) const
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
		throw Operand::Error("Div by zero!");
	else
	{
		switch (type)
		{
			case INT8:
			{
				auto rezult = std::stoll(_value_str) / std::stoll(ref.toString());
				if (rezult < SCHAR_MIN)
					throw Operand::Error("Underflow div on a rezult");
				else if (rezult > SCHAR_MAX)
					throw Operand::Error("Overflow div on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << rezult;
					return (new Operand(INT8, ss.str()));
				}
			}
			break;
			
			case INT16:
			{
				auto rezult = std::stoll(_value_str) / std::stoll(ref.toString());
				if (rezult < SHRT_MIN)
					throw Operand::Error("Underflow div on a rezult");
				else if (rezult > SHRT_MAX)
					throw Operand::Error("Overflow div on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << rezult;
					return (new Operand(INT16, ss.str()));
				}
			}
			break;

			case INT32:
			{
				auto rezult = std::stoll(_value_str) / std::stoll(ref.toString());
				if (rezult < INT_MIN)
					throw Operand::Error("Underflow div on a rezult");
				else if (rezult > INT_MAX)
					throw Operand::Error("Overflow div on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << rezult;
					return (new Operand(INT32, ss.str()));
				}
			}
			break;

			case FLOAT:
			{
				auto rezult = std::stold(_value_str) / std::stold(ref.toString());
				if (rezult < -FLT_MIN)
					throw Operand::Error("Underflow div on a rezult");
				else if (rezult > FLT_MAX)
					throw Operand::Error("Overflow div on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << std::setprecision(precision) << rezult;
					return (new Operand(FLOAT, ss.str()));
				}
			}
			break;
		
			case DOUBLE:
			{
				auto rezult = std::stold(_value_str) / std::stold(ref.toString());
				if (rezult < -DBL_MAX)
					throw Operand::Error("Underflow div on a rezult");
				else if (rezult > DBL_MAX)
					throw Operand::Error("Overflow div on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << std::setprecision(precision) << rezult;
					return (new Operand(DOUBLE, ss.str()));
				}
			}
			break;
		}
	}
	return nullptr;
}

IOperand *			Operand::operator%( IOperand const & ref ) const
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
				auto rezult = std::stoll(_value_str) % std::stoll(ref.toString());
				if (rezult < SCHAR_MIN)
					throw Operand::Error("Underflow mod on a rezult");
				else if (rezult > SCHAR_MAX)
					throw Operand::Error("Overflow mod on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << rezult;
					return (new Operand(INT8, ss.str()));
				}
			}
			break;
			
			case INT16:
			{
				auto rezult = std::stoll(_value_str) % std::stoll(ref.toString());
				if (rezult < SHRT_MIN)
					throw Operand::Error("Underflow mod on a rezult");
				else if (rezult > SHRT_MAX)
					throw Operand::Error("Overflow mod on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << rezult;
					return (new Operand(INT16, ss.str()));
				}
			}
			break;

			case INT32:
			{
				auto rezult = std::stoll(_value_str) % std::stoll(ref.toString());
				if (rezult < INT_MIN)
					throw Operand::Error("Underflow mod on a rezult");
				else if (rezult > INT_MAX)
					throw Operand::Error("Overflow mod on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << rezult;
					return (new Operand(INT32, ss.str()));
				}
			}
			break;

			case FLOAT:
			{
				auto rezult = fmod(std::stold(_value_str), std::stold(ref.toString()));
				if (rezult < -FLT_MIN)
					throw Operand::Error("Underflow mod on a rezult");
				else if (rezult > FLT_MAX)
					throw Operand::Error("Overflow mod on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << std::setprecision(precision) << rezult;
					return (new Operand(FLOAT, ss.str()));
				}
			}
			break;
		
			case DOUBLE:
			{
				auto rezult = fmod(std::stold(_value_str), std::stold(ref.toString()));
				if (rezult < -DBL_MAX)
					throw Operand::Error("Underflow mod on a rezult");
				else if (rezult > DBL_MAX)
					throw Operand::Error("Overflow mod on a rezult");
				else
				{
					std::stringstream ss (std::stringstream::out);
					ss << std::setprecision(precision) << rezult;
					return (new Operand(DOUBLE, ss.str()));
				}
			}
			break;
		}
	}
	return nullptr;
}

/********************************************************************/

Operand::Operand(eOperandType type, std::string const & value)
{
	_type = type;
	switch (_type)
	{
		case INT8:
		{
			bool		status = true;
			long long 	rezult;
			try
			{
				rezult = std::stoll(value);
			}
			catch (std::exception &e)
			{
				status = false;
				std::cout << "ERROR: " << e.what() << std::endl;
			}
			if (status == true)
			{
				if (rezult < SCHAR_MIN)
					throw Operand::Error("Underflow on a value");
				else if (rezult > SCHAR_MAX)
					throw Operand::Error("Overflow on a value");
				else
				{
					_precision = 0;
					std::stringstream ss(std::stringstream::out);
					ss << std::setprecision(_precision) << rezult;
					_value_str = ss.str();
				}
			}
			else
				throw Operand::Error("Operand not found");
		}
		break;
		
		case INT16:
		{
			bool		status = true;
			long long	rezult;
			try
			{
				rezult = std::stoll(value);
			}
			catch (std::exception &e)
			{
				status = false;
				std::cout << "ERROR: " << e.what() << std::endl;
			}
			if (status == true)
			{
				if (rezult < SHRT_MIN)
					throw Operand::Error("Underflow on a value");
				else if (rezult > SHRT_MAX)
					throw Operand::Error("Overflow on a value");
				else
				{
					_precision = 0;
					std::stringstream ss(std::stringstream::out);
					ss << std::setprecision(_precision) << rezult;
					_value_str = ss.str();
				}
			}
			else
				throw Operand::Error("Operand not found");
		}
		break;

		case INT32:
		{
			bool		status = true;
			long long	rezult;
			try
			{
				rezult = std::stoll(value);
			}
			catch (std::exception &e)
			{
				status = false;
				std::cout << "ERROR: " << e.what() << std::endl;
			}
			if (status == true)
			{
				if (rezult < INT_MIN)
					throw Operand::Error("Underflow on a value");
				else if (rezult > INT_MAX)
					throw Operand::Error("Overflow on a value");
				else
				{
					_precision = 0;
					std::stringstream ss(std::stringstream::out);
					ss << std::setprecision(_precision) << rezult;
					_value_str = ss.str();
				}
			}
			else
				throw Operand::Error("Operand not found");
		}
		break;

		case FLOAT:
		{
			bool		status = true;
			long double	rezult;
			try
			{
				rezult = std::stold(value);
			}
			catch (std::exception &e)
			{
				status = false;
				std::cout << "ERROR: " << e.what() << std::endl;
			}
			if (status == true)
			{
				if (rezult < -FLT_MAX)
					throw Operand::Error("Underflow on a value");
				else if (rezult > FLT_MAX)
					throw Operand::Error("Overflow on a value");
				else
				{
					_precision = FLT_DIG;
					std::stringstream ss(std::stringstream::out);
					ss << std::setprecision(_precision) << rezult;
					_value_str = ss.str();
				}
			}
			else
				throw Operand::Error("Operand not found");
		}
		break;
		
		case DOUBLE:
		{
			bool		status = true;
			long double	rezult;
			try
			{
				rezult = std::stold(value);
			}
			catch (std::exception &e)
			{
				status = false;
				std::cout << "ERROR: " << e.what() << std::endl;
			}
			if (status == true)
			{
				if (rezult < -DBL_MAX)
					throw Operand::Error("Underflow on a value");
				else if (rezult > DBL_MAX)
					throw Operand::Error("Overflow on a value");
				else
				{
					_precision = DBL_DIG;
					std::stringstream ss(std::stringstream::out);
					ss << std::setprecision(_precision) << rezult;
					_value_str = ss.str();
				}
			}
			else
				throw Operand::Error("Operand not found");
		}
		break;
	}
}

/********************************************************************/

int 				Operand::getPrecision() const
{
	return _precision;
}

eOperandType 		Operand::getType() const
{
	return _type;
}

std::string const &	Operand::toString() const
{
	return _value_str;	
}

/********************************************************************/

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
