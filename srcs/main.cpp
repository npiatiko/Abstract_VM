#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "Factory.hpp"
#include "Operand.hpp"
#include "Machine.hpp"
#include <map>
int main(int ac, char* av[]) {
	(void)ac;
	Machine machine(av[1]);
	machine.run();
/*	std::ifstream file("test");
	std::string raw;
	std::smatch matches;
	Factory fact;
	std::vector<IOperand const *> ops(0);
	std::map<std::string, eOperandType> types = {
			{"int8", eOperandType::Int8},
			{"int16", eOperandType::Int16},
			{"int32", eOperandType::Int32},
			{"float", eOperandType::Float},
			{"double", eOperandType::Double},
	};
	while (!file.eof()) {
		std::getline(file, raw);
		if (std::regex_match(raw, matches, std::regex("^([^;][^;]*)(;.*)*"))) {
			std::cout << "INSTR: " << matches.str(1) << std::endl;
			std::string instr = matches.str(1);
			if (std::regex_match(instr, matches, std::regex("(push )((int(8|16|32)\\([[:d:]]+\\))|(float|double)\\([[:d:]]+.[[:d:]]+\\))"))) {
				std::string value = matches.str(2);
				std::cout << "\t" << matches.str(1) << std::endl;
				std::cout << "\t\t" << value << std::endl;
				std::regex_match(value, matches, std::regex("([^\\(]*)\\((.*)\\)"));
				std::cout << "\t\t\t" << matches.str(1) << std::endl;
				std::cout << "\t\t\t\t" << matches.str(2) << std::endl;
				ops.push_back(fact.createOperand(types[matches.str(1)], matches.str(2)));
			} else if (instr == "add"){
				IOperand const *a = ops.back();
				ops.pop_back();
				IOperand const *b = ops.back();
				ops.pop_back();
				ops.push_back(*a + *b);
			}
		} else{
//			std::cout << "COMMENTS: " << raw << std::endl;
		}
	}
//	ops.push_back(fact.createOperand(eOperandType::Double, "12"));
//	ops.push_back(fact.createOperand(eOperandType::Int8, "8"));
*/
	return 0;
}
