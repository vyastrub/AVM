#include <iostream>
#include "session.hpp"
#include "definedFunctions.hpp"

namespace
{
	std::vector<std::string> ft_split(std::string && str)
	{
		std::string buf;
		std::vector<std::string> command;

		for (auto it = str.begin(); it < str.end(); ++it)
		{
			if (*it != ' ' && *it != ';')
				buf.push_back(*it);
			if (*it == ' ' || it + 1 == str.end())
			{
				if (!buf.empty())
					command.push_back(buf);
				buf.clear();
			}
			if (*it == ';')
			{
				if (!buf.empty())
					command.push_back(buf);
				break;
			}
		}
		return std::move(command);
	}
}

std::string Session::getCommand() const
{
	return _command;
}

Session::Error::Error(std::string what)
{
	_what = what;
}

char const * Session::Error::what() const throw()
{
	return _what.c_str();
}

Session::Session()
{
	_singleCallOption.emplace("pop", &Session::pop);
	_singleCallOption.emplace("dump", &Session::dump);
	_singleCallOption.emplace("add", &Session::add);
	_singleCallOption.emplace("sub", &Session::sub);
	_singleCallOption.emplace("mul", &Session::mul);
	_singleCallOption.emplace("div", &Session::div);
	_singleCallOption.emplace("mod", &Session::mod);
	_singleCallOption.emplace("print", &Session::print);

	_doubleCallOption.emplace("push", &Session::push);
	_doubleCallOption.emplace("assert", &Session::assert);

	_operandFactoryMap = {
		&Session::createInt8,
		&Session::createInt16,
		&Session::createInt32,
		&Session::createFloat,
		&Session::createDouble };
}

void	Session::run(std::string && command)
{
	if (_exit)
	{
		std::cout << "VM has closed" << std::endl;
		exit(0);
	}

	_command = command;
	std::vector<std::string> split_command = ft_split(std::move(command));
	if (split_command.size() == 0)
		return;

	auto i = _singleCallOption.find(split_command[0]);
	if (i != _singleCallOption.end() && split_command.size() == 1)
	{
		try
		{
			(this->*i->second)();
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR: " << e.what() << std::endl;
		}
		return;
	}

	auto j = _doubleCallOption.find(split_command[0]);
	if (j != _doubleCallOption.end() && split_command.size() == 2)
	{
		try
		{
			(this->*j->second)(split_command[1]);
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR: " << e.what() << std::endl;
		}
		return;
	}

	if (split_command[0] == "exit" && split_command.size() == 1)
		_exit = true;
	else
		throw Session::Error("'" + _command + "' - unknown command;");
}

void	Session::push(std::string command)
{
	Type type;
	try
	{
		type.setParam(command);
		_operands.emplace_back(createOperand(type.getEnumType(), type.getValue()));
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void	Session::pop()
{
	if (_operands.size() == 0)
		throw Session::Error("Pop on empty stack");
	_operands.pop_back();
}

void	Session::dump()
{
	if (_operands.size() == 0)
		throw Session::Error("Dump on empty stack");
	auto iter = _operands.size();
	while(iter > 0)
		std::cout << _operands[--iter]->toString() << std::endl;
}

void	Session::assert(std::string command)
{
	Type assert_type;
	if (_operands.size() == 0)
		throw Session::Error("Assert on empty stack");
	try
	{ 
		assert_type.setParam(command);
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
	if (_operands.back()->getType() != assert_type.getEnumType())
		throw Session::Error("different types can't been asserted");
	if (_operands.back()->toString() != assert_type.getValue())
		throw Session::Error("different values");
}

void	Session::add()
{
	OPERATION_FUNCTION_PATTERN(+)
}

void	Session::sub()
{
	OPERATION_FUNCTION_PATTERN(-)
}

void	Session::mul()
{
	OPERATION_FUNCTION_PATTERN(*)
}

void	Session::div()
{
	OPERATION_FUNCTION_PATTERN(/)
}

void	Session::mod()
{
	OPERATION_FUNCTION_PATTERN(%)
}

void	Session::print()
{
	if (_operands.size() == 0)
		throw Session::Error("Print on empty stack");
	if (_operands.back()->getType() != INT8)
		throw Session::Error("Only 8-bit integer can be printed");
	std::cout << static_cast<char>(std::stoi(_operands.back()->toString())) << std::endl;
}

IOperand* Session::createOperand(eOperandType type, const std::string & value)
{
	IOperand *new_element = nullptr;
	new_element = (this->*_operandFactoryMap[type])(value);
	if (new_element == nullptr)
		throw Session::Error("Can't create new element");		
  return new_element;
}

IOperand* Session::createInt8(const std::string & value)
{
	CREATE_OPERAND_PATTERN(INT8)
}

IOperand* Session::createInt16(const std::string & value)
{
	CREATE_OPERAND_PATTERN(INT16)
}

IOperand* Session::createInt32(const std::string & value)
{
	CREATE_OPERAND_PATTERN(INT32)
}

IOperand* Session::createFloat(const std::string & value)
{
	CREATE_OPERAND_PATTERN(FLOAT)
}

IOperand* Session::createDouble(const std::string & value)
{
	CREATE_OPERAND_PATTERN(DOUBLE)
}

std::ostream& operator<<(std::ostream &os, Session const & ref)
{
		os << ref.getCommand();
		return os;
}

std::ostream& operator<<(std::ostream &os, Session::Error const & ref)
{
	os << ref.what();
	return os;
}
