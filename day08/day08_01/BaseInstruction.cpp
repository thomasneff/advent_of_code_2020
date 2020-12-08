#include "BaseInstruction.h"

#include "SubInstructions.h"

BaseInstruction::BaseInstruction(ProcessorRegisters& reg, int arg) :
    reg(reg),
    arg(arg){

    };

std::unique_ptr<BaseInstruction> BaseInstruction::getInstructionFromString(const std::string& str, int arg, ProcessorRegisters& reg)
{
	if(str == "acc")
		return std::make_unique<AccInstruction>(reg, arg);
	else if(str == "jmp")
		return std::make_unique<JmpInstruction>(reg, arg);
	else if(str == "nop")
		return std::make_unique<NopInstruction>(reg, arg);

	// default - throw exception
	throw std::runtime_error(std::string("invalid instruction ") + str);
}