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
public:
	Instruction();
	virtual void execInstruction(std::vector<IOperand const *> &stack) = 0;
	virtual ~Instruction();
	Instruction(const Instruction &obj);
	Instruction &operator=(Instruction const &rhs);
};

class Push: public Instruction{
private:
	static Factory fact;
	IOperand const *_operand;
	static std::map<std::string, eOperandType> types;
public:
	void execInstruction(std::vector<IOperand const *> &stack) override;
	Push(int line, std::string const &str);
};
class Pop: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Dump: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Assert: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Add: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Sub: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Mul: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Div: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Mod: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Print: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
class Exit: public Instruction{
	void execInstruction(std::vector<IOperand const *> &stack) override;
};
#endif //INSTRUCTION_HPP
