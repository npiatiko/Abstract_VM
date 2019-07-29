//
// Created by Nickolay PIATIKOP on 2019-07-29.
//

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <iostream>
#include <exception>

class AVM_errors : public std::exception{
protected:
	std::string const _msg;
	AVM_errors();
	AVM_errors(const AVM_errors& obj);
	AVM_errors &operator=(AVM_errors const &rhs);
public:
	virtual ~AVM_errors();
	explicit AVM_errors(std::string const &msg);
	const char *what() const throw() override;
};

class Parce_errors : public AVM_errors{
public:
	explicit Parce_errors(std::string const &msg);
};
class Run_errors : public AVM_errors{
public:
	explicit Run_errors(std::string const &msg);
};
class exExit : public std::exception {
};
#endif //EXCEPTIONS_HPP
