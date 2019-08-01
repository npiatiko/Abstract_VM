//
// Created by Nickolay PIATIKOP on 2019-07-22.
//

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include <map>
#include <typeindex>

template <class T>
class Operand : public IOperand{
private:
	T				_value;
	eOperandType	_type;
	std::string		_sValue;
	Factory			_fact;
	static std::map<std::type_index, eOperandType> _types;
public:
	Operand(): _value(0), _type(eOperandType::Default){}
	Operand(T value): _value(value), _type(eOperandType::Default), _sValue(std::to_string(this->_value)){
		this->_type = Operand::_types[typeid(T)];
	}
	~Operand() override = default;
	Operand(const Operand &obj): _value(obj._value), _type(obj._type), _sValue(obj._sValue){}
	Operand &operator=(Operand const &rhs){
		this->_value = rhs._value;
		this->_type = rhs._type;
		this->_sValue = rhs._sValue;
		return *this;
	}
	int getPrecision() const override {
		return static_cast<int>(this->_type);
	}
	eOperandType getType() const override {
		return this->_type;
	}
	IOperand const *operator+(IOperand const &rhs) const override{
		eOperandType type = std::max(this->_type, rhs.getType());
		std::string result;
		if (type > eOperandType::Int32) {
			result = std::to_string(this->_value + std::stold(rhs.toString()));
		} else{
			result = std::to_string(this->_value + std::stoll(rhs.toString()));
		}
		return this->_fact.createOperand(type, result);
	}
	IOperand const *operator-( IOperand const & rhs ) const override{
		eOperandType type = std::max(this->_type, rhs.getType());
		std::string result;
		if (type > eOperandType::Int32) {
			result = std::to_string(this->_value - std::stold(rhs.toString()));
		} else{
			result = std::to_string(this->_value - std::stoll(rhs.toString()));
		}
		return this->_fact.createOperand(type, result);
	}
	IOperand const *operator*( IOperand const & rhs ) const override{
		eOperandType type = std::max(this->_type, rhs.getType());
		std::string result;
		if (type > eOperandType::Int32) {
			result = std::to_string(this->_value * std::stold(rhs.toString()));
		} else{
			result = std::to_string(this->_value * std::stoll(rhs.toString()));
		}
		return this->_fact.createOperand(type, result);
	}
	IOperand const *operator/( IOperand const & rhs ) const override{
		eOperandType type = std::max(this->_type, rhs.getType());
		std::string result;
		if (type > eOperandType::Int32) {
			result = std::to_string(this->_value / std::stold(rhs.toString()));
		} else{
			result = std::to_string(this->_value / std::stoll(rhs.toString()));
		}
		return this->_fact.createOperand(type, result);
	}
	IOperand const *operator%( IOperand const & rhs ) const override{
		return this->_fact.createOperand(std::max(this->_type, rhs.getType()), std::to_string(
				static_cast<int>(this->_value) % std::stoi(rhs.toString())));
	}
	std::string const &toString() const override{
		return this->_sValue;
	}

};
template <class T>
std::map<std::type_index, eOperandType> Operand<T>::_types = {
		{typeid(int8_t), eOperandType::Int8},
		{typeid(int16_t), eOperandType::Int16},
		{typeid(int32_t), eOperandType::Int32},
		{typeid(float), eOperandType::Float},
		{typeid(double), eOperandType::Double},
};
#endif //OPERAND_HPP
