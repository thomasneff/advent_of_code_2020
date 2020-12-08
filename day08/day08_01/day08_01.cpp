#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "BaseInstruction.h"
#include "ProcessorRegisters.h"

class Processor
{
public:
	Processor(std::vector<std::string> input_lines)
	{
		// Transform / parse input lines to instructions
		for(const auto& line : input_lines)
		{
			auto space_loc = line.find(' ');
			auto inst = line.substr(0, space_loc);
			int arg = std::stoi(line.substr(space_loc));

			instructions.push_back(BaseInstruction::getInstructionFromString(inst, arg, reg));
		}
	};

	bool executeInstruction()
	{
		// simply run instruction from current isp

		if(reg.isp < 0 || reg.isp >= instructions.size())
		{
			return false;
		}

		if(already_used_instructions.find(reg.isp) == already_used_instructions.end())
		{
			already_used_instructions[reg.isp] = true;
		}
		else
		{
			// we already executed this instruction
			return false;
		}

		instructions[reg.isp]->execute();

		return true;
	}

	ProcessorRegisters reg;

private:
	std::vector<std::unique_ptr<BaseInstruction>> instructions;

	// This is only for the challenge and wouldn't have a real use otherwise
	std::map<int, bool> already_used_instructions;
};

int main()
{
	std::ifstream input_file("input_simple.txt");

	std::string input_line;

	std::vector<std::string> input_lines;

	// get all input lines from file
	while(std::getline(input_file, input_line))
	{
		input_lines.push_back(input_line);
	}

	Processor p(input_lines);

	while(p.executeInstruction() == true)
		;

	std::cout << "Value in acc is: " << p.reg.acc << "\n";
}
