#include "machine.hpp"

#define OPERATION_FUNCTION_PATTERN(operation) 									\
	if (_operands.size() < 2)		    										\
		throw Machine::Error("The stack is composed of strictly	less that two " \
					   "values when an arithmetic instruction is executed");	\
	try																			\
	{																			\
		auto i = _operands.size();												\
		auto first = _operands.at(i - 2).get();									\
		auto second = _operands.at(i - 1).get();								\
		operandPtr result(*first operation *second);							\
		_operands.pop_back();													\
		_operands.pop_back();													\
		_operands.push_back(std::move(result)); 								\
	}																			\
	catch (std::exception &e)													\
	{																			\
			std::cout << "ERROR: " << e.what() << std::endl;					\
	}

#define CREATE_OPERAND_PATTERN(type)   					 \
	IOperand *new_element = nullptr;					 \
	try													 \
	{													 \
		new_element = new Operand(type, value);		 	 \
	}													 \
	catch (std::exception &e)							 \
	{													 \
		std::cout << "ERROR: " << e.what() << std::endl; \
	}													 \
	return(new_element);

namespace
{
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

Machine::Error::Error(std::string what) 
{
	_what = what;
}

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
	_singleCallOption.emplace("pop", &Machine::pop);
	_singleCallOption.emplace("dump", &Machine::dump);
	_singleCallOption.emplace("add", &Machine::add);
	_singleCallOption.emplace("sub", &Machine::sub);
	_singleCallOption.emplace("mul", &Machine::mul);
	_singleCallOption.emplace("div", &Machine::div);
	_singleCallOption.emplace("mod", &Machine::mod);
	_singleCallOption.emplace("print", &Machine::print);

	_doubleCallOption.emplace("push", &Machine::push); 
	_doubleCallOption.emplace("assert", &Machine::assert);
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
		throw Machine::Error("!" + command + "!:" + "An instruction is unknown");
}



void			Machine::push(std::string command)
{
	Type set_type;
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
	auto iter = _operands.size();
	while(iter > 0)
		std::cout << _operands[--iter]->toString() << std::endl;
}

void			Machine::assert(std::string command)
{
	Type assert_type;
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
	OPERATION_FUNCTION_PATTERN(+)
}

void			Machine::sub()
{
	OPERATION_FUNCTION_PATTERN(-)
}

void			Machine::mul()
{
	OPERATION_FUNCTION_PATTERN(*)
}

void			Machine::div()
{
	OPERATION_FUNCTION_PATTERN(/)
}

void			Machine::mod()
{
	OPERATION_FUNCTION_PATTERN(%)
}

void			Machine::print()
{
	if (_operands.size() == 0)
		throw Machine::Error("Instruction print on an empty stack");
	if (_operands.back()->getType() != INT8)
		throw Machine::Error("Instruction print on no 8-bit integer");
	std::cout << static_cast<char>(std::stoi(_operands.back()->toString())) << std::endl;
}

IOperand *		Machine::createOperand(eOperandType type, const std::string & value)
{
	IOperand *new_element = nullptr;

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
	if (new_element == nullptr)
		throw Machine::Error("Can not create new element");		
	return (new_element);
}

IOperand *		Machine::createInt8(const std::string & value)
{
	CREATE_OPERAND_PATTERN(INT8)
}

IOperand *		Machine::createInt16(const std::string & value)
{
	CREATE_OPERAND_PATTERN(INT16)
}

IOperand *		Machine::createInt32(const std::string & value)
{
	CREATE_OPERAND_PATTERN(INT32)
}

IOperand *		Machine::createFloat(const std::string & value)
{
	CREATE_OPERAND_PATTERN(FLOAT)
}

IOperand *		Machine::createDouble(const std::string & value)
{
	CREATE_OPERAND_PATTERN(DOUBLE)
}

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
