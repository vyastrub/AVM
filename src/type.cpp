#include <cctype>
#include "type.hpp"

/********************************************************************/


std::string			Type::get_type() const
{
	return _type;
}

std::string			Type::get_value() const
{
	return _value;
}

eOperandType	Type::get_enum_type() const
{
	if (_type.compare("int8") == 0)
		return (INT8);
	else if (_type.compare("int16") == 0)
		return (INT16);
	else if (_type.compare("int32") == 0)
		return (INT32);
	else if (_type.compare("float") == 0)
		return (FLOAT);
	else if (_type.compare("double") == 0)
		return (DOUBLE);
	return (DOUBLE);
}

/********************************************************************/

Type::Error::Error(std::string what) : _what(what) {}


std::string	Type::Error::get_error() const
{
	return _what;
}

char const* Type::Error::what() const throw()
{
	return _what.c_str();
}

/********************************************************************/

void	Type::set_param(std::string command)
{
	set_type(command);
	set_value(command);
}

void					Type::set_type(std::string & type)
{
	if (type.compare(0, 4, "int8") == 0)
	{
		_type = "int8";
		type.erase(type.begin(), type.begin() + 4);
	}
	else if (type.compare(0, 5, "int16") == 0)
	{
		_type = "int16";
		type.erase(type.begin(), type.begin() + 5);
	}
	else if (type.compare(0, 5, "int32") == 0)
	{
		_type = "int32";
		type.erase(type.begin(), type.begin() + 5);
	}
	else if (type.compare(0, 5, "float") == 0)
	{
		_type = "float";
		type.erase(type.begin(), type.begin() + 5);
	}
	else if (type.compare(0, 6, "double") == 0)
	{
		_type = "double";
		type.erase(type.begin(), type.begin() + 6);
	}
	else
		throw Type::Error("!" + type + "!:" + "Unknown type");
}

void	Type::set_value(std::string  & value)
{
	if (value.front() == '(' && value.back() == ')')
	{
		value.erase(value.begin());
		value.erase(value.end() - 1);

		int	status_error = 0;
		int	status_digit = 0;
		int	status_minus = 0;
		int	status_point = 0;
		auto  buff = value;

		if (_type == "int8" || _type == "int16" || _type == "int32")
			status_point = 1;

		while (!value.empty() && status_error == 0)
		{
			if (std::isdigit(value.front()))
			{
				_value += value.front();
				status_digit++;
			}
			else if (value.front() == '-')
			{
				if (status_digit != 0)
					status_error++;
				_value += value.front();
				status_minus++;
			}
			else if (value.front() == '.')
			{
				if (status_digit == 0 || status_point != 0)
					status_error++;
				_value += value.front();
				status_point++;
			}
			value.erase(value.begin());	
		}
		if (status_error != 0)
			throw Type::Error("!" + buff + "!:" + "GRAMMAR ERROR");
	}
	else
		throw Type::Error("!" + value + "!:" + "GRAMMAR ERROR");
}

/********************************************************************/

std::ostream &	operator<<(std::ostream &os, Type const & ref)
{
	os << ref.get_type() << ":" << ref.get_value();
	return os;
}

std::ostream &	operator<<(std::ostream &os, Type::Error const & ref)
{
	os << ref.get_error();
	return os;
}
