//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#include <regex>
#include "Instruction.hpp"

Instruction::Instruction(): _line(0), _rhs(nullptr), _lhs(nullptr){

}
Instruction::~Instruction() = default;
Instruction::Instruction(const Instruction &obj): _line(obj._line) {

}
Instruction &Instruction::operator=(Instruction const &rhs) {
	this->_line = rhs._line;
	return *this;
}
Instruction::Instruction(int line): Instruction(){
	this->_line = line;
}
std::map<std::string, eOperandType> Instruction::types = {
	{"int8", eOperandType::Int8},
	{"int16", eOperandType::Int16},
	{"int32", eOperandType::Int32},
	{"float", eOperandType::Float},
	{"double", eOperandType::Double},
};
void Instruction::execInstruction(std::vector<IOperand const *> &stack) {
	this->_rhs = stack.back();
	stack.pop_back();
	this->_lhs = stack.back();
	stack.pop_back();
}
Push::Push(int line, std::string const &value): Instruction(line){
	std::smatch match;
	std::regex_match(value, match, std::regex("^\\s*([^\\(]*)\\((.*)\\)\\s*$"));
	std::string tmp0 = match.str(0);
	std::string tmp1 = match.str(1);
	std::string tmp2 = match.str(2);
	this->_operand = Instruction::fact.createOperand(Instruction::types[match.str(1)], match.str(2));
}
void Push::execInstruction(std::vector<IOperand const *> &stack) {
	stack.push_back(this->_operand);
}
void Pop::execInstruction(std::vector<IOperand const *> &stack) {
	this->_lhs = stack.back();
	stack.pop_back();
}
Pop::Pop(int line) : Instruction(line) {

}
void Dump::execInstruction(std::vector<IOperand const *> &stack) {
	for (auto i = stack.end(); i >= stack.begin(); ++i) {
		std::cout << (*i)->toString() << std::endl;
	}
}
Dump::Dump(int line) : Instruction(line) {

}
void Assert::execInstruction(std::vector<IOperand const *> &) {

}
Assert::Assert(int line, std::string const &value): Instruction(line){
	std::smatch match;
	std::regex_match(value, match, std::regex("^\\s*([^\\(]*)\\((.*)\\)\\s*$"));
	std::string tmp0 = match.str(0);
	std::string tmp1 = match.str(1);
	std::string tmp2 = match.str(2);
	this->_operand = Instruction::fact.createOperand(Instruction::types[match.str(1)], match.str(2));
}
void Add::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs + *this->_rhs);
}
Add::Add(int line) : Instruction(line) {

}
void Sub::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs - *this->_rhs);
}
Sub::Sub(int line) : Instruction(line) {

}
void Mul::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs * *this->_rhs);
}
Mul::Mul(int line) : Instruction(line) {

}
void Div::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs / *this->_rhs);
}
Div::Div(int line) : Instruction(line) {

}
void Mod::execInstruction(std::vector<IOperand const *> &) {

}
Mod::Mod(int line) : Instruction(line) {

}
void Print::execInstruction(std::vector<IOperand const *> &) {

}
Print::Print(int line) : Instruction(line) {

}
void Exit::execInstruction(std::vector<IOperand const *> &) {

}
Exit::Exit(int line) : Instruction(line) {

}
Factory Instruction::fact;
