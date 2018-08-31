#pragma once
#include<string>

typedef enum 	eOperandType
{
				INT8,
				INT16,
				INT32,
				FLOAT,
				DOUBLE,
}				eOperandType;

class 	IOperand
{
	public:
virtual int 			getPrecision( void ) const = 0;		// Precision of the type of the instance
virtual eOperandType	getType( void ) const = 0;			// Type of the instance

virtual IOperand *		operator+(const IOperand & ref) const = 0;	// Sum
virtual IOperand *		operator-(const IOperand & ref) const = 0;	// Difference
virtual IOperand *		operator*(const IOperand & ref) const = 0;	// Product
virtual IOperand *		operator/(const IOperand & ref) const = 0;	// Quotient
virtual IOperand *		operator%(const IOperand & ref) const = 0;	// Modulo

virtual std::string const & toString() const = 0;			// String representation of the instance

virtual ~IOperand() {}
};

