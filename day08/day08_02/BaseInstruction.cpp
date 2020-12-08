#include "BaseInstruction.h"

#include "SubInstructions.h"

BaseInstruction::BaseInstruction(ProcessorRegisters& reg, int arg, std::string inst) :
    reg(reg),
    arg(arg),
    inst(inst){

    };

std::unique_ptr<BaseInstruction> BaseInstruction::getInstructionFromString(const std::string& str, int arg, ProcessorRegisters& reg)
{
	if(str == "acc")
		return std::make_unique<AccInstruction>(reg, arg, str);
	else if(str == "jmp")
		return std::make_unique<JmpInstruction>(reg, arg, str);
	else if(str == "nop")
		return std::make_unique<NopInstruction>(reg, arg, str);

	// default - throw exception
	throw std::runtime_error(std::string("invalid instruction ") + str);
}