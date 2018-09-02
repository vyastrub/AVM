#pragma once
#include <vector>
#include <memory>
#include <map>
#include "operand.hpp"
#include "type.hpp"

class Session;
typedef std::unique_ptr<IOperand> operandPtr;
typedef std::map<std::string, void(Session::*)()> singleFunctionMap_mt;
typedef std::map<std::string, void(Session::*)(std::string)> doubleFunctionMap_mt;
typedef std::vector<IOperand*(Session::*)(const std::string &)> operandFactoryMap_vt;

class Session
{
public:

	Session();
	Session(Session const &ref) = delete;
	~Session() = default;
	Session & operator=(Session const &ref) = delete;
	std::string	getCommand() const;
	void run(std::string && command);
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

	class Error : public std::exception
	{
	public:
		Error() = default;
		Error(std::string what);
		Error(Error const &) = default;
		~Error() = default;
		Error &	operator=(Error const &) = default;
		char const * what() const throw();
	private:
		std::string	_what;
	};

private:
	bool					_exit;
	std::string				_command;
	std::vector<operandPtr>	_operands;
	singleFunctionMap_mt	_singleCallOption;
	doubleFunctionMap_mt	_doubleCallOption;
	operandFactoryMap_vt	_operandFactoryMap;

	IOperand *	createOperand(eOperandType type, const std::string & value);
	IOperand *	createInt8(const std::string &);
	IOperand *	createInt16(const std::string &);
	IOperand *	createInt32(const std::string &);
	IOperand *	createFloat(const std::string &);
	IOperand *	createDouble(const std::string &);
};

std::ostream &		operator<<(std::ostream & os, Session const & ref);
std::ostream &		operator<<(std::ostream & os, Session::Error const & ref);
