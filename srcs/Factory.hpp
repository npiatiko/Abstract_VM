//
// Created by Nickolay PIATIKOP on 2019-07-22.
//

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "IOperand.hpp"

class Factory {
private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
public:
	Factory();
	~Factory();
	Factory(const Factory &obj);
	Factory &operator=(Factory const &rhs);
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
};


#endif //FACTORY_HPP
