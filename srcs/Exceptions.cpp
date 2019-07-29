//
// Created by Nickolay PIATIKOP on 2019-07-29.
//

#include "Exceptions.hpp"

const char *AVM_errors::what() const throw(){
	return this->_msg.c_str();
}
AVM_errors::AVM_errors(std::string const &msg): _msg(msg){
}
AVM_errors::AVM_errors() :_msg(nullptr){

}
AVM_errors::~AVM_errors() {

}
AVM_errors::AVM_errors(const AVM_errors &obj): _msg(obj._msg){

}
AVM_errors &AVM_errors::operator=(AVM_errors const &) {
	return *this;
}
Parce_errors::Parce_errors(std::string const &msg) : AVM_errors(msg) {

}
Run_errors::Run_errors(std::string const &msg) : AVM_errors(msg) {

}
