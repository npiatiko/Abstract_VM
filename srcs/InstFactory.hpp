//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#ifndef INSTFACTORY_HPP
#define INSTFACTORY_HPP
#include <iostream>
#include <map>

class Instruction;

class instFactory {
private:
	static std::map<std::string, int> _instrTypes;
	Instruction *createPush(int line, std::string const &arg);
	Instruction *createPop(int line, std::string const &arg);
	Instruction *createDump(int line, std::string const &arg);
	Instruction *createAssert(int line, std::string const &arg);
	Instruction *createAdd(int line, std::string const &arg);
	Instruction *createSub(int line, std::string const &arg);
	Instruction *createMul(int line, std::string const &arg);
	Instruction *createDiv(int line, std::string const &arg);
	Instruction *createMod(int line, std::string const &arg);
	Instruction *createPrint(int line, std::string const &arg);
	Instruction *createExit(int line, std::string const &arg);
public:
	Instruction *createInstr(int line, std::string const &str);
};


#endif //INSTFACTORY_HPP
