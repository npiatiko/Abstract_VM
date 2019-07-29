//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#include "InstFactory.hpp"
#include "Instruction.hpp"
#include <regex>
#include "Exceptions.hpp"

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
	std::regex_match(str, matches, std::regex("^\\s*([^\\s]+)\\s*(.*)\\s*$"));
	auto instrType = instFactory::_instrTypes.find(matches.str(1));
	std::string tmp0 = matches.str(0);
	std::string tmp1 = matches.str(1);
	std::string tmp2 = matches.str(2);
	if (instrType == instFactory::_instrTypes.end()){
		throw Parce_errors("Unknown instruction \"" + matches.str(1) + "\"");
	}
	return (this->*fPtr[instrType->second])(line, matches.str(2));
}
Instruction *instFactory::createPush(int line, std::string const &arg) {
	return new Push(line, arg);
}
Instruction *instFactory::createPop(int line, std::string const &arg) {
	return new Pop(line, arg);
}
Instruction *instFactory::createDump(int line, std::string const &arg) {
	return new Dump(line, arg);
}
Instruction *instFactory::createAssert(int line, std::string const &arg) {
	return new Assert(line, arg);
}
Instruction *instFactory::createAdd(int line, std::string const &arg) {
	return new Add(line, arg);
}
Instruction *instFactory::createSub(int line, std::string const &arg) {
	return new Sub(line, arg);
}
Instruction *instFactory::createMul(int line, std::string const &arg) {
	return new Mul(line, arg);
}
Instruction *instFactory::createDiv(int line, std::string const &arg) {
	return new Div(line, arg);
}
Instruction *instFactory::createMod(int line, std::string const &arg) {
	return new Mod(line, arg);
}
Instruction *instFactory::createPrint(int line, std::string const &arg) {
	return new Print(line, arg);
}
Instruction *instFactory::createExit(int line, std::string const &arg) {
	return new Exit(line, arg);
}
