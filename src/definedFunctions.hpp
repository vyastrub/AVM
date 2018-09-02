#pragma once

#define FACTORY_FUNCTION(type, function, min, max, prec)				\
	bool		status = true;											\
	long type 	result;													\
	try																	\
	{																	\
		result = function(value);										\
	}																	\
	catch (std::exception &e)											\
	{																	\
		status = false;													\
		std::cout << "ERROR: " << e.what() << std::endl;				\
	}																	\
	if (status == true)													\
	{																	\
		if (result < min)												\
			throw Operand::Error("Value is less than the minimum");		\
		else if (result > max)											\
			throw Operand::Error("Value is greater than the maximum");	\
		_precision = prec;												\
		std::stringstream ss(std::stringstream::out);					\
		ss << std::setprecision(_precision) << result;					\
		_value_str = ss.str();											\
	}																	\
	else																\
		throw Operand::Error("Operand not found");

#define OPERATION_PATTERN(operation, float_point_result_equation)						\
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
				throw Operand::Error("Result is less than the type minimum value");		\
			else if (result > SCHAR_MAX)												\
				throw Operand::Error("Result is grater than the type maximum value");	\
			std::stringstream ss (std::stringstream::out);								\
			ss << result;																\
			return (new Operand(INT8, ss.str()));										\
		}																				\
		case INT16:																		\
		{																				\
			auto result = std::stoll(_value_str) operation std::stoll(ref.toString());	\
			if (result < SHRT_MIN)														\
				throw Operand::Error("Result is less than the type minimum value"); 	\
			else if (result > SHRT_MAX)													\
				throw Operand::Error("Result is grater than the type maximum value");	\
			std::stringstream ss (std::stringstream::out);								\
			ss << result;																\
			return (new Operand(INT16, ss.str()));										\
		}																				\
		case INT32:																		\
		{																				\
			auto result = std::stoll(_value_str) operation std::stoll(ref.toString());	\
			if (result < INT_MIN)														\
				throw Operand::Error("Result is less than the type minimum value");		\
			else if (result > INT_MAX)													\
				throw Operand::Error("Result is grater than the type maximum value");	\
			std::stringstream ss (std::stringstream::out);								\
			ss << result;																\
			return (new Operand(INT32, ss.str()));										\
		}																				\
		case FLOAT:																		\
		{																				\
			auto result = float_point_result_equation;									\
			if (result < -FLT_MIN)														\
				throw Operand::Error("Result is less than the type minimum value");		\
			else if (result > FLT_MAX)													\
				throw Operand::Error("Result is grater than the type maximum value");	\
			std::stringstream ss (std::stringstream::out);								\
			ss << std::setprecision(precision) << result;								\
			return (new Operand(FLOAT, ss.str()));										\
		}																				\
		case DOUBLE:																	\
		{																				\
			auto result = float_point_result_equation;									\
			if (result < -DBL_MAX)														\
				throw Operand::Error("Result is less than the type minimum value");		\
			else if (result > DBL_MAX)													\
				throw Operand::Error("Result is grater than the type maximum value");	\
			std::stringstream ss (std::stringstream::out);								\
			ss << std::setprecision(precision) << result;								\
			return (new Operand(DOUBLE, ss.str()));										\
		}																				\
	}																					\
	return nullptr;

#define OPERATION_FUNCTION_PATTERN(operation) 										\
	if (_operands.size() < 2)		    											\
		throw Session::Error("There must be at least two elements in the stack");	\
	try																				\
	{																				\
		auto i = _operands.size();													\
		auto first = _operands.at(i - 2).get();										\
		auto second = _operands.at(i - 1).get();									\
		operandPtr result(*first operation *second);								\
		_operands.pop_back();														\
		_operands.pop_back();														\
		_operands.push_back(std::move(result)); 									\
	}																				\
	catch (std::exception &e)														\
	{																				\
			std::cout << "ERROR: " << e.what() << std::endl;						\
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
