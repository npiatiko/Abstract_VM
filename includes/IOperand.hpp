//
// Created by Nickolay PIATIKOP on 2019-07-16.
//
#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <iostream>

enum class eOperandType {Int8 = 0, Int16, Int32, Float, Double, Default};

class IOperand {
public:
	virtual int getPrecision() const = 0; // Precision of the _type of the instance
	virtual eOperandType getType() const = 0; // Type of the instance
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
	virtual std::string const &toString() const = 0; // String representation of the instance
	virtual ~IOperand() {}
};
#endif