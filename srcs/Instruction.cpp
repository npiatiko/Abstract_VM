//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#include "Instruction.hpp"

Instruction::Instruction(): _line(0){

}
Instruction::~Instruction() = default;
Instruction::Instruction(const Instruction &obj): _line(obj._line) {

}
Instruction &Instruction::operator=(Instruction const &rhs) {
	this->_line = rhs._line;
	return *this;
}
std::map<std::string, eOperandType> Push::types = {
	{"int8", eOperandType::Int8},
	{"int16", eOperandType::Int16},
	{"int32", eOperandType::Int32},
	{"float", eOperandType::Float},
	{"double", eOperandType::Double},
};
Push::Push(int line, std::string const &){
	this->_line = line;
	this->_operand = fact.createOperand(types["Int8"], "5");
}
void Push::execInstruction(std::vector<IOperand const *> &stack) {
	stack.push_back(this->_operand);
}

void Pop::execInstruction(std::vector<IOperand const *> &) {

}
void Dump::execInstruction(std::vector<IOperand const *> &) {

}
void Assert::execInstruction(std::vector<IOperand const *> &) {

}
void Add::execInstruction(std::vector<IOperand const *> &) {

}
void Sub::execInstruction(std::vector<IOperand const *> &) {

}
void Mul::execInstruction(std::vector<IOperand const *> &) {

}
void Div::execInstruction(std::vector<IOperand const *> &) {

}
void Mod::execInstruction(std::vector<IOperand const *> &) {

}
void Print::execInstruction(std::vector<IOperand const *> &) {

}
void Exit::execInstruction(std::vector<IOperand const *> &) {

}
Factory Push::fact;
