#include <cctype>
#include "type.hpp"

namespace
{
	static const std::vector<std::string> types = {"int8", "int16", "int32", "float", "double"};
}

std::string	 Type::get_type() const
{
	return _type;
}

std::string	 Type::get_value() const
{
	return _value;
}

eOperandType Type::get_enum_type() const
{
	for (size_t i{}; i < types.size(); ++i)
		if (_type.compare(types[i]) == 0)
			return static_cast<eOperandType>(i);
	return (DOUBLE);
}

Type::Error::Error(std::string what) : _what(what) {}

std::string	Type::Error::get_error() const
{
	return _what;
}

char const* Type::Error::what() const throw()
{
	return _what.c_str();
}

void	Type::set_param(std::string command)
{
	set_type(command);
	set_value(command);
}

void	Type::set_type(std::string & type)
{
	for (auto i = types.begin(); i < types.end(); ++i)
		if (type.compare(0, (*i).size(), *i) == 0)
		{
			_type = *i;
			type.erase(type.begin(), type.begin() + (*i).size());
			return;
		}
	throw Type::Error("!" + type + "!:" + "Unknown type");
}

void	Type::set_value(std::string  & value)
{
	if (value.front() != '(' || value.back() != ')')
	{
		throw Type::Error("!" + value + "!:" + "GRAMMAR ERROR");
	}

	value.erase(value.begin());
	value.erase(value.end() - 1);

	auto  buff = value;
	int	status_error = 0, status_digit = 0, status_minus = 0, status_point = 0;
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
