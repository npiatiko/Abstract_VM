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
	Instruction *createPush(int line, std::string const &str);
	Instruction *createPop(int line, std::string const &str);
	Instruction *createDump(int line, std::string const &str);
	Instruction *createAssert(int line, std::string const &str);
	Instruction *createAdd(int line, std::string const &str);
	Instruction *createSub(int line, std::string const &str);
	Instruction *createMul(int line, std::string const &str);
	Instruction *createDiv(int line, std::string const &str);
	Instruction *createMod(int line, std::string const &str);
	Instruction *createPrint(int line, std::string const &str);
	Instruction *createExit(int line, std::string const &str);
public:
	Instruction *createInstr(int line, std::string const &str);
//	instFactory();
//	~instFactory();
//	instFactory(const instFactory &obj);
//	instFactory &operator=(instFactory const &rhs);

};


#endif //INSTFACTORY_HPP
