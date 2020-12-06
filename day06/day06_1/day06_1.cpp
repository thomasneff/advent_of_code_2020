#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<std::string> input_lines;

	// get all input numbers from file
	while(std::getline(input_file, input_line))
	{
		input_lines.push_back(input_line);
	}

	// add another empty string for parsing at the end
	input_lines.push_back("");

	// count individual/unique answers for each group, collect the sum.
	// groups are separated by newlines, individuals in each line
	std::set<char> answers;
	int total_num_answers = 0;
	for(const auto& line : input_lines)
	{
		if(line.empty())
		{
			total_num_answers += answers.size();
			std::cout << "answers for group: " << answers.size() << "\n";
			answers.clear();
		}
		else
		{
			// Read lines into answers
			for(const auto& c : line)
			{
				answers.insert(c);
			}
		}
	}
	std::cout << "Total number of answers: " << total_num_answers << "\n";
}
