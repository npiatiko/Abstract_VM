//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#include <regex>
#include "Instruction.hpp"
#include "Exceptions.hpp"
#include "Machine.hpp"
#include <algorithm>
#include <cassert>
#include <sstream>
#include <iomanip>

Factory Instruction::fact;
Instruction::Instruction(): _line(0), _rhs(nullptr), _lhs(nullptr), _operand(nullptr){

}
Instruction::~Instruction() {
	delete(this->_operand);
	delete(this->_rhs);
	delete(this->_lhs);
}
Instruction::Instruction(const Instruction &): Instruction(){

}
Instruction &Instruction::operator=(Instruction const &rhs) {
	this->_line = rhs._line;
	return *this;
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
		throw Run_errors("too few operands in stack");
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
			throw Parce_errors("Invalid argument \"" + arg + "\"");
		}
		auto type = Instruction::types.find(match.str(1));
		if (type == Instruction::types.end()) {
			throw Parce_errors("Invalid type of operand \"" + match.str(1) + "\"");
		}
		this->_operand = Instruction::fact.createOperand(type->second, match.str(2));
	}
}
int Instruction::getLine() const {
	return _line;
}
void Instruction::ThrowException(int line) {
	if (Machine::isFlag()){
		std::cout << MAGENTA << "Warning: Line: " << line << ": To many instruction arguments\n" << DEFAULT;
	} else {
		throw Parce_errors("To many instruction arguments");
	}
}
Push::Push(int line, std::string const &arg): Instruction(line, arg){
	if (!this->_operand){
		throw Parce_errors("To few instruction arguments" );
	}
}
void Push::execInstruction(std::vector<IOperand const *> &stack) {
	stack.push_back(this->_operand);
	this->_operand = nullptr;
}
void Pop::execInstruction(std::vector<IOperand const *> &stack) {
	if (stack.empty()){
		throw Run_errors("Pop on empty stack");
	}
	this->_lhs = stack.back();
	stack.pop_back();
}
Pop::Pop(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand) {
		this->ThrowException(line);
	}
}
void Dump::execInstruction(std::vector<IOperand const *> &stack) {
	for (auto wrapIter : stack) {
		if (wrapIter->getPrecision() < 3) {
			std::cout << wrapIter->toString() << std::endl;
		} else {
			std::cout << std::fixed << std::setprecision(2) << std::stold(wrapIter->toString()) << std::endl;
		}
	}
}
Dump::Dump(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Assert::execInstruction(std::vector<IOperand const *> &stack) {
	if (stack.empty()){
		throw Run_errors("Stack is empty");
	}
	if(stack.back()->getType() != this->_operand->getType()){
		throw Run_errors("Assertion error");
	} else if(stack.back()->toString() != this->_operand->toString()){
		throw Run_errors("Assertion error");
	}
}
Assert::Assert(int line, std::string const &arg): Instruction(line, arg){
	if (!this->_operand){
		throw Parce_errors("To few instruction arguments" );
	}
}
void Add::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs + *this->_rhs);
}
Add::Add(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Sub::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs - *this->_rhs);
}
Sub::Sub(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Mul::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	stack.push_back(*this->_lhs * *this->_rhs);
}
Mul::Mul(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Div::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	if (std::stold(this->_rhs->toString()) == 0.0){
		throw Run_errors("div by zero");
	}
	stack.push_back(*this->_lhs / *this->_rhs);
}
Div::Div(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Mod::execInstruction(std::vector<IOperand const *> &stack) {
	Instruction::execInstruction(stack);
	if (std::max(this->_lhs->getType(), this->_rhs->getType()) > eOperandType::Int32){
		throw Run_errors("incompatible operands with mod");
	} else if (!std::stoi(this->_rhs->toString())){
		throw Run_errors("mod by zero");
	}
	stack.push_back(*this->_lhs % *this->_rhs);
}
Mod::Mod(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Print::execInstruction(std::vector<IOperand const *> &stack) {
	if (stack.empty()){
		throw Run_errors("Stack is empty");
	}
	if (stack.back()->getType() > eOperandType::Int8){
		throw Run_errors("to large operand");
	} else{
		char c = std::stoi(stack.back()->toString());
		if (std::isprint(c)){
			std::cout << c << std::endl;
		} else{
			std::cout << "\"non printable\"" << std::endl;
		}
	}
}
Print::Print(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Exit::execInstruction(std::vector<IOperand const *> &) {
	throw exExit();
}
Exit::Exit(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
Min::Min(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Min::execInstruction(std::vector<IOperand const *> &stack) {
	if (!stack.empty()) {
		IOperand const *min = *stack.begin();
		for (auto & wrapIter : stack) {
			if (std::stold(wrapIter->toString()) < std::stold(min->toString())){
				min = wrapIter;
			}
		}
		std::cout << "MIN: ";
		if (min->getPrecision() < 3) {
			std::cout << min->toString() << std::endl;
		} else {
			std::cout << std::fixed << std::setprecision(2) << std::stold(min->toString()) << std::endl;
		}
	}
}
Max::Max(int line, std::string const &arg) : Instruction(line, arg) {
	if (this->_operand){
		this->ThrowException(line);
	}
}
void Max::execInstruction(std::vector<IOperand const *> &stack) {
	if (!stack.empty()) {
		IOperand const *max = *stack.begin();
		for (auto & wrapIter : stack) {
			if (std::stold(wrapIter->toString()) > std::stold(max->toString())){
				max = wrapIter;
			}
		}
		std::cout << "MIN: ";
		if (max->getPrecision() < 3) {
			std::cout << max->toString() << std::endl;
		} else {
			std::cout << std::fixed << std::setprecision(2) << std::stold(max->toString()) << std::endl;
		}
	}
}
