#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "Factory.hpp"
#include "Operand.hpp"
#include "Machine.hpp"
#include <map>
int main(int ac, char* av[]) {
	int flag = Machine::ParseFlag(ac, av);
	if (ac - flag > 1) {
		int i = 1 + flag;
		try {
			for (; i < ac; ++i) {
				Machine machine(av[i]);
				machine.run();
			}
		}
		catch (std::invalid_argument &e){
			std::cout << av[i] << ": " << e.what() << std::endl;
		}
	} else{
		Machine machine;
		machine.run();
	}
	return 0;
}
