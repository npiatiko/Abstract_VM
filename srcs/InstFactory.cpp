//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#include "InstFactory.hpp"
#include "Instruction.hpp"

Instruction *instFactory::createInstr(int line, std::string const &str){

	return this->createPush(line, str);
}
std::map<std::string, int> instFactory::_instrTypes = {
		{"push",	0},
		{"pop",		1},
		{"dump",	2},
		{"assert",	3},
		{"add",		4},
		{"sub",		5},
		{"mul",		6},
		{"div",		7},
		{"mod",		8},
		{"print",	9},
		{"exit",	10},
};
Instruction *instFactory::createPush(int line, std::string const &str) {
	return new Push(line, str);
}
Instruction *instFactory::createPop(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createDump(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createAssert(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createAdd(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createSub(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createMul(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createDiv(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createMod(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createPrint(int line, std::string &str) {
	return nullptr;
}
Instruction *instFactory::createExit(int line, std::string &str) {
	return nullptr;
}
