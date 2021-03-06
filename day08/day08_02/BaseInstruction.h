#pragma once
#include <memory>
#include <string>

#include "ProcessorRegisters.h"

class BaseInstruction
{
public:
	BaseInstruction(ProcessorRegisters& reg, int arg, std::string inst);

	virtual void execute() = 0;

	static std::unique_ptr<BaseInstruction> getInstructionFromString(const std::string& str, int arg, ProcessorRegisters& reg);

	std::string getInstructionName() { return inst; }

protected:
	ProcessorRegisters& reg;
	int arg;
	std::string inst;
};
