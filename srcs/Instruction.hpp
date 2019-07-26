//
// Created by Nickolay PIATIKOP on 2019-07-24.
//

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <map>
#include "IOperand.hpp"
#include "Factory.hpp"
#include <vector>

class Instruction {
protected:
	int _line;
	static std::map<std::string, eOperandType> types;
	static Factory fact;
	IOperand const *_rhs, *_lhs;
public:
	Instruction();
	Instruction(int line);
	Instruction(int line, std::string const &arg);
	virtual void execInstruction(std::vector<IOperand const *> &stack);
	virtual ~Instruction();
	Instruction(const Instruction &obj);
	Instruction &operator=(Instruction const &rhs);
};

class Push: public Instruction{
private:
	IOperand const *_operand;
public:
	void execInstruction(std::vector<IOperand const *> &stack) override;
	Push(int line, std::string const &arg);
};

class Pop: public Instruction{
public:
	Pop(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Dump: public Instruction{
public:
	Dump(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Assert: public Instruction{
private:
	IOperand const *_operand;
public:
	Assert(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Add: public Instruction{
public:
	Add(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Sub: public Instruction{
public:
	Sub(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Mul: public Instruction{
public:
	Mul(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Div: public Instruction{
public:
	Div(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Mod: public Instruction{
public:
	Mod(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Print: public Instruction{
public:
	Print(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};

class Exit: public Instruction{
public:
	Exit(int line, std::string const &arg);
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
#endif //INSTRUCTION_HPP
