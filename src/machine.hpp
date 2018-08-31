#pragma once
#include <vector>
#include "operand.hpp"
#include "type.hpp"

typedef std::unique_ptr<IOperand> operandPtr;

class Machine 
{

public:

	Machine() = default;
	Machine(Machine const &ref) = delete;
	~Machine() = default;
	Machine &	operator=(Machine const &ref) = delete;

	std::string	get_command() const;

	void run(std::string command);
	void push(std::string command);
	void pop();
	void dump();
	void assert(std::string command);
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print();


	class 		Error : public std::exception
	{
	public:
		Error() = default;
		Error(std::string what);
		Error(Error const &) = default;
		~Error() = default;
		Error &	operator=(Error const &) = default;

		std::string	get_error() const;
		char const * what() const throw();
	private:
		std::string	_what;
	};

private:
	bool						_exit;
	std::string					_command;
	std::vector<operandPtr>		_operands;

	IOperand *	createOperand(eOperandType type, const std::string & value);
	IOperand *	createInt8(const std::string &);
	IOperand *	createInt16(const std::string &);
	IOperand *	createInt32(const std::string &);
	IOperand *	createFloat(const std::string &);
	IOperand *	createDouble(const std::string &);
};

std::ostream &		operator<<(std::ostream & os, Machine const & ref);
std::ostream &		operator<<(std::ostream & os, Machine::Error const & ref);
