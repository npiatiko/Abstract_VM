//
// Created by Nickolay PIATIKOP on 2019-07-22.
//

#include "Factory.hpp"
#include "Operand.hpp"
#include <cfloat>
#include <regex>

Factory::Factory() {
}
Factory::~Factory() {

}
Factory::Factory(const Factory &) {

}
Factory &Factory::operator=(Factory const &) {
	return *this;
}
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
		throw std::range_error("Bad value \"" + value + "\"");
	}
	std::string tmp0 = match.str(0);
	std::string tmp1 = match.str(1);
	std::string tmp2 = match.str(2);

	return (this->*fPtr[static_cast<int >(type)])(match.str(1));
}
IOperand const *Factory::createInt8(std::string const &value) const {
	size_t pos = 0;
	long long tmp = std::stoll(value, &pos, 10);
	if (value[pos]){
		throw std::range_error ("Bad value \"" + value + "\"");
	} else if (tmp > INT8_MAX){
		throw std::overflow_error (value);
	} else if (tmp < INT8_MIN){
		throw std::underflow_error (value);
	}
	return new Operand<int8_t >(static_cast<int8_t >(tmp));
}
IOperand const *Factory::createInt16(std::string const &value) const {
	size_t pos = 0;
	long long tmp = std::stoll(value, &pos, 10);
	if (value[pos]){
		throw std::range_error ("Bad value \"" + value + "\"");
	} else if (tmp > INT16_MAX){
		throw std::overflow_error (value);
	} else if (tmp < INT16_MIN){
		throw std::underflow_error (value);
	}
	return new Operand<int16_t >(static_cast<int16_t >(tmp));
}
IOperand const *Factory::createInt32(std::string const &value) const {
	size_t pos = 0;
	long long tmp = std::stoll(value, &pos, 10);
	if (value[pos]){
		throw std::range_error ("Bad value \"" + value + "\"");
	} else if (tmp > INT32_MAX){
		throw std::overflow_error (value);
	} else if (tmp < INT32_MIN){
		throw std::underflow_error (value);
	}
	return new Operand<int32_t >(static_cast<int32_t >(tmp));
}
IOperand const *Factory::createFloat(std::string const &value) const {
	size_t pos = 0;
	long double tmp = std::stold(value, &pos);
	if (value[pos]){
		throw std::range_error ("Bad value \"" + value + "\"");
	} else if (tmp > FLT_MAX){
		throw std::overflow_error (value);
	} else if (tmp < -FLT_MAX){
		throw std::underflow_error (value);
	}
	return new Operand<float >(static_cast<float >(tmp));
}
IOperand const *Factory::createDouble(std::string const &value) const {
	size_t pos = 0;
	long double tmp = std::stold(value, &pos);
	if (value[pos]){
		throw std::range_error ("Bad value \"" + value + "\"");
	} else if (tmp > DBL_MAX){
		throw std::overflow_error (value);
	} else if (tmp < -DBL_MAX){
		throw std::underflow_error (value);
	}
	return new Operand<double >(static_cast<double >(tmp));
}
