//
// Created by Nickolay PIATIKOP on 2019-07-24.
//
#include <regex>
#include <fstream>
#include <iostream>
#include "Machine.hpp"
#include <exception>
#include <sstream>
#include "Exceptions.hpp"

bool Machine::_flag = false;

Machine::Machine(): _exit(false), _error(false){
	std::string raw;
	std::stringstream input;
	std::smatch matches;
	while (raw != ";;"){
		std::getline(std::cin, raw);
		input << raw << std::endl;
	}
	this->Parser(input);
}
Machine::~Machine() {
	for (auto i : this->_instrns){
		delete(i);
	}
	for (auto j : this->_stack){
		delete(j);
	}
}
Machine::Machine(const Machine &): _exit(false), _error(false) {

}
Machine &Machine::operator=(Machine const &) {
	return *this;
}
Machine::Machine(char *filename): _exit(false), _error(false){
	std::ifstream filestream(filename);
	std::stringstream input;
	std::smatch matches;
	if (!filestream.is_open() || !filestream.good()){
		throw std::invalid_argument("file wasn't opened");
	}
	input << filestream.rdbuf();
	filestream.close();
	this->Parser(input);
}
void Machine::run() {
	if (!Machine::_error) {
		auto i = this->_instrns.begin();
		try {
			for (; i < this->_instrns.end(); ++i) {
				(*i)->execInstruction(this->_stack);
			}
			if (!Machine::_exit) {
				std::cout << "Run error: instruction \"Exit\" not found" << std::endl;
			}
		}
		catch (exExit &) {
			Machine::_exit = true;
		}
		catch (Run_errors &e) {
			std::cout << "Run error: Line " << (*i)->getLine() << " : Error : " << e.what() << std::endl;
		}
	}
}
void Machine::Parser(std::stringstream &input) {
	std::string raw;
	std::smatch matches;
	int line = 1;
	while (!input.eof()) {
		std::getline(input, raw);
		try {
			if (std::regex_match(raw, matches, std::regex("^([^;][^;]*)(;.*)*"))) {
				this->_instrns.push_back(this->_factoryinst.createInstr(line, matches.str(1)));
			}
		}
		catch(Parce_errors &e){
			Machine::_error = true;
			std::cout << "Parse error: Line " << line << " : Error : " << e.what() << std::endl;
		}
		++line;
	}
}
int Machine::ParseFlag(int &ac, char **av) {
	if (ac > 1){
		if (std::string(av[1]) == "-e"){
			Machine::_flag = true;
			return 1;
		}
	}
	return 0;
}
bool Machine::isFlag() {
	return _flag;
}
