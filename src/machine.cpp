#include "machine.hpp"



namespace {

	std::vector<std::string> ft_split(std::string str) {
		std::string buf;
		std::vector<std::string> command;

		for (auto it = str.begin(); it < str.end(); ++it) {
			if (*it != ' ' && *it != ';')
				buf.push_back(*it);
			if (*it == ' ' || it + 1 == str.end()) {
				if (!buf.empty())
					command.push_back(buf);
				buf.clear();
			}
			if (*it == ';') {
				if (!buf.empty())
					command.push_back(buf);
				break;
			}
		}
		return std::move(command);
	}
}

std::string 		Machine::get_command() const
{
	return _command;
}

Machine::Error::Error(std::string what) :_what{what} {}

std::string	Machine::Error::get_error() const
{
	return _what;
}

char const * Machine::Error::what() const throw()
{
	return _what.c_str();
}

Machine::Machine()
{
	_singleCallOption = {{"pop", &Machine::pop},
						{"dump", &Machine::dump},
						{"add", &Machine::add},
						{"sub", &Machine::sub}, 
						{"mul", &Machine::mul},
						{"div", &Machine::div},
						{"mod", &Machine::mod},
						{"print", &Machine::print}};

	_doubleCallOption = {{"push", &Machine::push}, {"assert", &Machine::assert}};
}

void	Machine::run(std::string command)
{
	if (_exit)
	{
		std::cout << "VM has closed" << std::endl;
		exit(0);
	}

	_command = command;
	std::vector<std::string> split_command = ft_split(command);

	if (split_command.size() == 0)
	{
		return;
	}
	for (auto i = _doubleCallOption.begin(); i != _doubleCallOption.end(); ++i)
	{
		if (split_command[0] == i->first && split_command.size() == 2)
		{
			try
			{
				i->second()(split_command[1]);
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR: " << e.what() << std::endl;
			}
			return;
		}
	}
	for (auto i = _singleCallOption.begin(); i != _singleCallOption.end(); ++i)
	{
		if (split_command[0] == i->first && split_command.size() == 1)
		{
			try
			{
				i->second();
 			}
			catch (std::exception &e)
			{
				std::cout << "ERROR: " << e.what() << std::endl;
			}
			return;
		}
	}
	if (split_command[0] == "exit" && split_command.size() == 1)
		_exit = true;
	else
		throw Machine::Error("!" + command + "!:" + "An instruction is unknown");
}

/********************************************************************/

void			Machine::push(std::string command)
{
	Type 		set_type;
	try
	{
		set_type.set_param(command);
		_operands.emplace_back(createOperand(set_type.get_enum_type(), set_type.get_value()));
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void			Machine::pop()
{
	if (_operands.size() == 0)
		throw Machine::Error("Instruction pop on an empty stack");
	_operands.pop_back();
}

void			Machine::dump()
{
	if (_operands.size() == 0)
		throw Machine::Error("Instruction dump on an empty stack");
	else
	{
		auto iter = _operands.size();
		while(iter > 0)
			std::cout << _operands[--iter]->toString() << std::endl;
	}
}

void			Machine::assert(std::string command)
{
	Type 	assert_type;
	if (_operands.size() == 0)
		throw Machine::Error("Instruction assert on an empty stack");
	try
	{
		assert_type.set_param(command);
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
	if (_operands.back()->getType() != assert_type.get_enum_type())
		throw Machine::Error("An assert instruction is not true: different type");
	if (_operands.back()->toString() != assert_type.get_value())
		throw Machine::Error("An assert instruction is not true: different value");
}

void			Machine::add()
{
	if (_operands.size() < 2)
		throw Machine::Error("The stack is composed of strictly less that two values when an arithmetic instruction is executed");
	try
	{
		auto i = _operands.size();
		auto first = _operands.at(i - 2).get();
		auto second = _operands.at(i - 1).get();
		operandPtr result(*first + *second);
		_operands.pop_back();
		_operands.pop_back();
		_operands.push_back(std::move(result)); 
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void			Machine::sub()
{
	if (_operands.size() < 2)
		throw Machine::Error("The stack is composed of strictly less that two values when an arithmetic instruction is executed");
	try
	{
		auto i = _operands.size();
		auto first = _operands.at(i - 2).get();
		auto second = _operands.at(i - 1).get();
		operandPtr result(*first - *second);
		_operands.pop_back();
		_operands.pop_back();
		_operands.push_back(std::move(result));
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void			Machine::mul()
{
	if (_operands.size() < 2)
		throw Machine::Error("The stack is composed of strictly less that two values when an arithmetic instruction is executed");
	try
	{
		auto i = _operands.size();
		auto first = _operands.at(i - 2).get();
		auto second = _operands.at(i - 1).get();
		operandPtr result(*first * *second);
		_operands.pop_back();
		_operands.pop_back();
		_operands.push_back(std::move(result));
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void			Machine::div()
{
	if (_operands.size() < 2)
		throw Machine::Error("The stack is composed of strictly less that two values when an arithmetic instruction is executed");
	try
	{
		auto i = _operands.size();
		auto first = _operands.at(i - 2).get();
		auto second = _operands.at(i - 1).get();
		operandPtr result(*first / *second);
		_operands.pop_back();
		_operands.pop_back();
		_operands.push_back(std::move(result));
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void			Machine::mod()
{
	if (_operands.size() < 2)
		throw Machine::Error("The stack is composed of strictly less that two values when an arithmetic instruction is executed");
	try
	{
		auto i = _operands.size();
		auto first = _operands.at(i - 2).get();
		auto second = _operands.at(i - 1).get();
		operandPtr result(*first % *second);
		_operands.pop_back();
		_operands.pop_back();
		_operands.push_back(std::move(result));
	}
	catch (std::exception &e)
	{
			std::cout << "ERROR: " << e.what() << std::endl;
	}
}

void			Machine::print()
{
	if (_operands.size() == 0)
		throw Machine::Error("Instruction print on an empty stack");
	if (_operands.back()->getType() != INT8)
		throw Machine::Error("Instruction print on no 8-bit integer");
	std::cout << static_cast<char>(std::stoi(_operands.back()->toString())) << std::endl;
}

/********************************************************************/

IOperand *		Machine::createOperand(eOperandType type, const std::string & value)
{
	IOperand *new_element = NULL;

	switch (type)
	{
		case INT8:
		new_element = createInt8(value);
		break;
		
		case INT16:
		new_element = createInt16(value);
		break;

		case INT32:
		new_element = createInt32(value);
		break;

		case FLOAT:
		new_element = createFloat(value);
		break;
		
		case DOUBLE:
		new_element = createDouble(value);
		break;
	}
	if (new_element == NULL)
		throw Machine::Error("Can not create new element");		

  return (new_element);
}

IOperand *		Machine::createInt8(const std::string & value)
{
	IOperand *new_element = NULL;
	try
	{
		new_element = new Operand(INT8, value);
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return(new_element);
}

IOperand *		Machine::createInt16(const std::string & value)
{
	IOperand *new_element = NULL;
	try
	{
		new_element = new Operand(INT16, value);
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return(new_element);
}

IOperand *		Machine::createInt32(const std::string & value)
{
	IOperand *new_element = NULL;
	try
	{
		new_element = new Operand(INT32, value);
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return(new_element);
}

IOperand *		Machine::createFloat(const std::string & value)
{
	IOperand *new_element = NULL;
	try
	{
		new_element = new Operand(FLOAT, value);
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return(new_element);
}

IOperand *		Machine::createDouble(const std::string & value)
{
	IOperand *new_element = NULL;
	try
	{
		new_element = new Operand(DOUBLE, value);
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return(new_element);
}

 

/********************************************************************/

std::ostream &			operator<<(std::ostream &os, Machine const & ref)
{
		os << ref.get_command();
		return os;
}

std::ostream &			operator<<(std::ostream &os, Machine::Error const & ref)
{
	os << ref.get_error();
	return os;
}
