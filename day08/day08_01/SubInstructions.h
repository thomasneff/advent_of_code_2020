#pragma once
#include <iostream>

#include "BaseInstruction.h"
#include "ProcessorRegisters.h"

class AccInstruction : public BaseInstruction
{
public:
	AccInstruction(ProcessorRegisters& reg, int arg) : BaseInstruction(reg, arg){};
	void execute()
	{
		// TODO:
		std::cout << "Executing AccInstruction at isp " << reg.isp << " with arg " << arg << "\n";
		reg.isp++;
		reg.acc += arg;
	}
};

class JmpInstruction : public BaseInstruction
{
public:
	JmpInstruction(ProcessorRegisters& reg, int arg) : BaseInstruction(reg, arg){};
	void execute()
	{
		// TODO:
		std::cout << "Executing JmpInstruction at isp " << reg.isp << " with arg " << arg << "\n";
		reg.isp += arg;
	}
};

class NopInstruction : public BaseInstruction
{
public:
	NopInstruction(ProcessorRegisters& reg, int arg) : BaseInstruction(reg, arg){};
	void execute()
	{
		// TODO:
		std::cout << "Executing NopInstruction at isp " << reg.isp << " with arg " << arg << "\n";
		reg.isp++;
	}
};