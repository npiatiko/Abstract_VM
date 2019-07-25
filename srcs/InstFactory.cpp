//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#include "InstFactory.hpp"
#include "Instruction.hpp"
#include <regex>

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
Instruction *instFactory::createInstr(int line, std::string const &str){
	static Instruction *(instFactory::*fPtr[])(int , std::string const &) = {
			&instFactory::createPush,
			&instFactory::createPop,
			&instFactory::createDump,
			&instFactory::createAssert,
			&instFactory::createAdd,
			&instFactory::createSub,
			&instFactory::createMul,
			&instFactory::createDiv,
			&instFactory::createMod,
			&instFactory::createPrint,
			&instFactory::createExit,
	};
	std::smatch matches;
	std::regex_match(str, matches, std::regex("^\\s*([^\\s]+) *(.*)\\s*$"));
	std::string tmp0 = matches.str(0);
	std::string tmp1 = matches.str(1);
	std::string tmp2 = matches.str(2);
	return (this->*fPtr[instFactory::_instrTypes[matches.str(1)]])(line, matches.str(2));
}
Instruction *instFactory::createPush(int line, std::string const &str) {
	return new Push(line, str);
}
Instruction *instFactory::createPop(int line, std::string const &) {
	return new Pop(line);
}
Instruction *instFactory::createDump(int line, std::string const &) {
	return new Dump(line);
}
Instruction *instFactory::createAssert(int line, std::string const &str) {
	return new Assert(line, str);
}
Instruction *instFactory::createAdd(int line, std::string const &) {
	return new Add(line);
}
Instruction *instFactory::createSub(int line, std::string const &) {
	return new Sub(line);
}
Instruction *instFactory::createMul(int line, std::string const &) {
	return new Mul(line);
}
Instruction *instFactory::createDiv(int line, std::string const &) {
	return new Div(line);
}
Instruction *instFactory::createMod(int line, std::string const &) {
	return new Mod(line);
}
Instruction *instFactory::createPrint(int line, std::string const &) {
	return new Print(line);
}
Instruction *instFactory::createExit(int line, std::string const &) {
	return new Exit(line);
}
