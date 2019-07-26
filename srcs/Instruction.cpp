//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#include <regex>
#include "Instruction.hpp"
#include <algorithm>

Instruction::Instruction(): _line(0), _rhs(nullptr), _lhs(nullptr), _operand(nullptr){

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
	if (stack.size() < 2){
		throw std::runtime_error("too few operands in stack");
	}
	this->_rhs = stack.back();
	stack.pop_back();
	this->_lhs = stack.back();
	stack.pop_back();
}
Instruction::Instruction(int line, std::string const &arg): Instruction() {
	this->_line = line;
	if (arg.length()) {
		std::smatch match;
		if (!std::regex_match(arg, match, std::regex("^\\s*([^\\(|^\\s]*)\\s*\\((.*)\\)\\s*$"))) {
			throw std::logic_error("Invalid argument \"" + arg + "\"");
		}
		std::string tmp0 = match.str(0);
		std::string tmp1 = match.str(1);
		std::string tmp2 = match.str(2);
		auto type = Instruction::types.find(match.str(1));
		if (type == Instruction::types.end()) {
			throw std::logic_error("Invalid type of operand \"" + match.str(1) + "\"");
		}
		this->_operand = Instruction::fact.createOperand(type->second, match.str(2));
	}
}
Push::Push(int line, std::string const &arg): Instruction(line, arg){

}
void Push::execInstruction(std::vector<IOperand const *> &stack) {
	stack.push_back(this->_operand);
}
void Pop::execInstruction(std::vector<IOperand const *> &stack) {
	this->_lhs = stack.back();
	stack.pop_back();
}
Pop::Pop(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"" );
	}
}
void Dump::execInstruction(std::vector<IOperand const *> &stack) {
	std::vector<IOperand const *> tmp = stack;
	std::reverse(tmp.begin(), tmp.end());
	for (auto i : tmp) {
		std::cout << i->toString() << std::endl;
	}
}
Dump::Dump(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
void Assert::execInstruction(std::vector<IOperand const *> &) {

}
Assert::Assert(int line, std::string const &arg): Instruction(line, arg){
}
void Add::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs + *this->_rhs);
}
Add::Add(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
void Sub::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs - *this->_rhs);
}
Sub::Sub(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
void Mul::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs * *this->_rhs);
}
Mul::Mul(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
void Div::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	if (!std::stoi(this->_rhs->toString())){
		throw std::runtime_error("div by zero");
	}
	stack.push_back(*this->_lhs / *this->_rhs);
}
Div::Div(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
void Mod::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	if (std::max(this->_lhs->getType(), this->_rhs->getType()) > eOperandType::Int32){
		throw std::runtime_error("incompatible operands with mod");
	} else if (!std::stoi(this->_rhs->toString())){
		throw std::runtime_error("mod by zero");
	}
	stack.push_back(*this->_lhs % *this->_rhs);
}
Mod::Mod(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
void Print::execInstruction(std::vector<IOperand const *> &stack) {
	this->_rhs = stack.back();
	stack.pop_back();
	if (this->_rhs->getType() > eOperandType::Int8){
		throw std::overflow_error("to large operand");
	} else{
		char c = std::stoi(this->_rhs->toString());
		if (std::isprint(c)){
			std::cout << c << std::endl;
		} else{
			std::cout << "\"non printable\"" << std::endl;
		}
	}
}
Print::Print(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
void Exit::execInstruction(std::vector<IOperand const *> &) {

}
Exit::Exit(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		throw std::logic_error("To many instruction arguments \"");
	}
}
Factory Instruction::fact;
