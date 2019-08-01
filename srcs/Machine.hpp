//
// Created by Nickolay PIATIKOP on 2019-07-24.
//
#ifndef MACHINE_HPP
#define MACHINE_HPP
#include "Instruction.hpp"
#include <vector>
#include "InstFactory.hpp"
#define RED "\033[31m"
#define DEFAULT "\033[0m"
#define MAGENTA "\033[95m"
class Machine {
private:
	bool _exit, _error;
	static bool _flag;
	std::vector<Instruction *> _instrns;
	instFactory _factoryinst;
	std::vector<IOperand const *> _stack;
	void Parser(std::stringstream &input, std::string const &inputName);
public:
	Machine(char *file);
	Machine();
	~Machine();
	Machine(const Machine &obj);
	Machine &operator=(Machine const &rhs);
	void run();
	static int ParseFlag(int &ac, char **av);
	static bool isFlag();
};


#endif //MACHINE_HPP
