//
// Created by Nickolay PIATIKOP on 2019-07-22.
//

#include "Factory.hpp"
#include "Operand.hpp"
#include "Exceptions.hpp"
#include <cfloat>
#include <regex>

IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const {
	static IOperand const *(Factory::*fPtr[])(std::string const &) const = {
			&Factory::createInt8,
			&Factory::createInt16,
			&Factory::createInt32,
			&Factory::createFloat,
			&Factory::createDouble
	};
	std::smatch match;
	if (!std::regex_match(value, match, std::regex("^\\s*(-?\\d*\\.?\\d*)\\s*$"))){
		throw Parce_errors("Bad value \"" + value + "\"");
	}
	try {
		return (this->*fPtr[static_cast<int >(type)])(match.str(1));
	}
	catch (Parce_errors &){
		throw ;
	}
	catch (std::exception &e){
		if (match.str(1)[0] == '-') {
			throw Parce_errors("Underflow error \"" + match.str(1) + "\"");
		} else{
			throw Parce_errors("Overflow error \"" + match.str(1) + "\"");
		}
	}
}
IOperand const *Factory::createInt8(std::string const &value) const {
	size_t pos = 0;
	long long tmp = std::stoll(value, &pos, 10);
	if (value[pos]){
		throw Parce_errors ("Bad value \"" + value + "\"");
	} else if (tmp > INT8_MAX){
		throw Parce_errors ("Type Int8 overflow \"" + value + "\"");
	} else if (tmp < INT8_MIN){
		throw Parce_errors ("Type Int8 underflow \"" + value + "\"");
	}
	return new Operand<int8_t >(static_cast<int8_t >(tmp));
}
IOperand const *Factory::createInt16(std::string const &value) const {
	size_t pos = 0;
	long long tmp = std::stoll(value, &pos, 10);
	if (value[pos]){
		throw Parce_errors ("Bad value \"" + value + "\"");
	} else if (tmp > INT16_MAX){
		throw Parce_errors ("Type Int16 overflow \"" + value + "\"");
	} else if (tmp < INT16_MIN){
		throw Parce_errors ("Type Int16 underflow \"" + value + "\"");
	}
	return new Operand<int16_t >(static_cast<int16_t >(tmp));
}
IOperand const *Factory::createInt32(std::string const &value) const {
	size_t pos = 0;
	long long tmp = std::stoll(value, &pos, 10);
	if (value[pos]){
		throw Parce_errors ("Bad value \"" + value + "\"");
	} else if (tmp > INT32_MAX){
		throw Parce_errors ("Type Int32 overflow \"" + value + "\"");
	} else if (tmp < INT32_MIN){
		throw Parce_errors ("Type Int32 underflow \"" + value + "\"");
	}
	return new Operand<int32_t >(static_cast<int32_t >(tmp));
}
IOperand const *Factory::createFloat(std::string const &value) const {
	size_t pos = 0;
	if (!std::regex_match(value, std::regex("^[^\\.]*\\..*$"))){
		throw Parce_errors ("Bad value \"" + value + "\"");
	}
	long double tmp = std::stold(value, &pos);
	if (value[pos]){
		throw Parce_errors ("Bad value \"" + value + "\"");
	} else if (tmp > FLT_MAX){
		throw Parce_errors ("Type float positive overflow \"" + value + "\"");
	} else if (tmp < -FLT_MAX){
		throw Parce_errors ("Type float negative overflow \"" + value + "\"");
	}
	return new Operand<float >(static_cast<float >(tmp));
}
IOperand const *Factory::createDouble(std::string const &value) const {
	size_t pos = 0;
	if (!std::regex_match(value, std::regex("^[^\\.]*\\..*$"))){
		throw Parce_errors ("Bad value \"" + value + "\"");
	}
	long double tmp = std::stold(value, &pos);
	if (value[pos]){
		throw Parce_errors ("Bad value \"" + value + "\"");
	} else if (tmp > DBL_MAX){
		throw Parce_errors ("Type double positive overflow \"" + value + "\"");
	} else if (tmp < -DBL_MAX){
		throw Parce_errors ("Type double negative overflow \"" + value + "\"");
	}
	return new Operand<double >(static_cast<double >(tmp));
}
