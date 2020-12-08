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

enum ProcessorReturn
{
	Executed,
	Terminated,
	Repeated
};

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

	Processor(std::vector<std::string> input_lines, int change_index)
	{
		// This constructor changes the change_index'th occurance of jmp or nop to each other.
		// Transform / parse input lines to instructions

		int nop_or_jmp_count = 0;
		for(const auto& line : input_lines)
		{
			auto space_loc = line.find(' ');
			auto inst = line.substr(0, space_loc);
			int arg = std::stoi(line.substr(space_loc));

			if((inst == "nop" || inst == "jmp"))
			{
				if(change_index == nop_or_jmp_count)
				{
					if(inst == "nop")
						inst = "jmp";
					else
						inst = "nop";
				}

				nop_or_jmp_count++;
			}

			instructions.push_back(BaseInstruction::getInstructionFromString(inst, arg, reg));
		}
	};

	ProcessorReturn executeInstruction()
	{
		// simply run instruction from current isp

		if(reg.isp < 0 || reg.isp >= instructions.size())
		{
			return ProcessorReturn::Terminated;
		}

		if(already_used_instructions.find(reg.isp) == already_used_instructions.end())
		{
			already_used_instructions[reg.isp] = true;
		}
		else
		{
			// we already executed this instruction.
			// std::cout << "Already executed this instruction! " << reg.isp << "\n";
			return ProcessorReturn::Repeated;
		}

		instructions[reg.isp]->execute();

		return ProcessorReturn::Executed;
	}

	ProcessorRegisters reg;

private:
	std::vector<std::unique_ptr<BaseInstruction>> instructions;

	// This is only for the challenge and wouldn't have a real use otherwise
	std::map<int, bool> already_used_instructions;
};

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<std::string> input_lines;

	// get all input lines from file
	while(std::getline(input_file, input_line))
	{
		input_lines.push_back(input_line);
	}

	for(int i = 0; i < input_lines.size(); i++)
	{
		Processor p(input_lines, i);
		ProcessorReturn ret = ProcessorReturn::Executed;

		while(true)
		{
			ret = p.executeInstruction();

			if(ret != ProcessorReturn::Executed)
				break;
		}

		if(ret == ProcessorReturn::Terminated)
		{
			std::cout << "Terminated! Value in acc is: " << p.reg.acc << "\n";
			break;
		}
		else
		{
			std::cout << "Repeated value for change_index == " << i << "\n";
		}
	}
}
