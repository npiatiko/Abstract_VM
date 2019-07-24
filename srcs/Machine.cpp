//
// Created by Nickolay PIATIKOP on 2019-07-24.
//
#include <regex>
#include <fstream>
#include <iostream>
#include "Machine.hpp"
#include <exception>

Machine::Machine() {

}
Machine::~Machine() {
}
Machine::Machine(const Machine &) {

}
Machine &Machine::operator=(Machine const &) {
	return *this;
}
Machine::Machine(char *filename){
	std::ifstream filestream(filename);
	std::string raw;
	std::smatch matches;
	int line = 1;
	if (!filestream.is_open() || !filestream.good()){
		throw std::invalid_argument("File not opened");
	}
	while (!filestream.eof()) {
		std::getline(filestream, raw);
		if (std::regex_match(raw, matches, std::regex("^([^;][^;]*)(;.*)*"))) {
			this->_instrns.push_back(this->_factoryinst.createInstr(line, matches.str(1)));
		}
		++line;
	}
	filestream.close();
}
void Machine::run() {
	for (auto i = this->_instrns.begin(); i < this->_instrns.end(); ++i) {
	}
}
