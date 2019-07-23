//
// Created by Nickolay PIATIKOP on 2019-07-22.
//

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "Factory.hpp"

template <class T>
class Operand : public IOperand{
private:
	T				_value;
	eOperandType	_type;
	std::string		_sValue;
	Factory			_fact;
public:
	Operand(): _value(0), _type(eOperandType::Default){}
	Operand(T value): _value(value), _type(eOperandType::Default), _sValue(std::to_string(this->_value)){
		if (typeid(T) == typeid(int8_t)){
			this->_type = eOperandType::Int8;
		} else if (typeid(T) == typeid(int16_t)){
			this->_type = eOperandType::Int16;
		} else if (typeid(T) == typeid(int32_t)){
			this->_type = eOperandType::Int32;
		}  else if (typeid(T) == typeid(float)){
			this->_type = eOperandType::Float;
		} else if (typeid(T) == typeid(double)){
			this->_type = eOperandType::Double;
		}
	}
	~Operand() override = default;
	Operand(const Operand &obj): _value(obj._value), _type(obj._type){}
	Operand &operator=(Operand const &rhs){
		this->_value = rhs._value;
		this->_type = rhs._type;
		return *this;
	}
	int getPrecision() const override {
		return static_cast<int>(this->_type);
	}
	eOperandType getType() const override {
		return this->_type;
	}
	IOperand const *operator+(IOperand const &rhs) const override{
		return this->_fact.createOperand(std::max(this->_type, rhs.getType()), std::to_string(this->_value + std::stod(rhs.toString())));
	}
	IOperand const *operator-( IOperand const & rhs ) const override{
		return &rhs;
	}
	IOperand const *operator*( IOperand const & rhs ) const override{
		return &rhs;
	}
	IOperand const *operator/( IOperand const & rhs ) const override{
		return &rhs;
	}
	IOperand const *operator%( IOperand const & rhs ) const override{
		return &rhs;
	}
	std::string const &toString() const override{
		return this->_sValue;
	}

};

#endif //OPERAND_HPP
