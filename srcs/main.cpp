#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "Factory.hpp"
#include "Operand.hpp"
#include "Machine.hpp"
#include <map>

int main(int ac, char* av[]) {
	try {
		int flag = Machine::ParseFlag(ac, av);
		if (ac - flag > 1) {
			int i = 1 + flag;
			for (; i < ac; ++i) {
				std::cout << av[i] << ":\n";
				try {
					Machine machine(av[i]);
					machine.run();
				}
				catch (std::invalid_argument &e) {
					std::cout << RED << av[i] << ": " << e.what() << DEFAULT << std::endl;
				}
			}
		} else {
			Machine machine;
			machine.run();
		}
	}
	catch (std::exception &e){
		std::cout << RED << "Unknown error :" << e.what() << DEFAULT << std::endl;
	}
	catch (...){
		std::cout << RED << "Unknown error." << DEFAULT << std::endl;
	}
	return 0;
}
