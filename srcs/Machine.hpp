//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "Instruction.hpp"
#include <vector>
#include "InstFactory.hpp"

class Machine {
private:
	std::vector<Instruction *> _instrns;
	instFactory _factoryinst;
public:
	Machine(char *file);
	Machine();
	~Machine();
	Machine(const Machine &obj);
	Machine &operator=(Machine const &rhs);
	void run();
};


#endif //MACHINE_HPP
