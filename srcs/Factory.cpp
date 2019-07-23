//
// Created by Nickolay PIATIKOP on 2019-07-22.
//

#include "Factory.hpp"
#include "Operand.hpp"

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
	(void)type;
	static IOperand const *(Factory::*fPtr[])(std::string const &) const =
			{&Factory::createInt8, &Factory::createInt16, &Factory::createInt32, &Factory::createFloat, &Factory::createDouble};
	return (this->*fPtr[static_cast<int>(type)])(value);
}
IOperand const *Factory::createInt8(std::string const &value) const {
	return new Operand<int8_t>(std::stoi(value));
}
IOperand const *Factory::createInt16(std::string const &value) const {
	return new Operand<int16_t>(std::stoi(value));
}
IOperand const *Factory::createInt32(std::string const &value) const {
	return new Operand<int32_t>(std::stoi(value));
}
IOperand const *Factory::createFloat(std::string const &value) const {
	return new Operand<float>(std::stof(value));
}
IOperand const *Factory::createDouble(std::string const &value) const {
	return new Operand<double>(std::stod(value));
}
