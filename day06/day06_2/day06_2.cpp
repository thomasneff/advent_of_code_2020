#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
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

	std::unordered_map<char, int> num_answers;
	int total_num_answers = 0;
	int num_people_in_group = 0;
	for(const auto& line : input_lines)
	{
		if(line.empty())
		{
			// Check if everyone has the same answer
			int num_answers_from_everyone_in_group = 0;
			for(const auto& pair : num_answers)
			{
				if(pair.second == num_people_in_group)
					num_answers_from_everyone_in_group++;
			}

			std::cout << "answers for group: " << num_answers_from_everyone_in_group << "\n";
			num_answers.clear();
			total_num_answers += num_answers_from_everyone_in_group;
			num_people_in_group = 0;
		}
		else
		{
			// Read lines into answers
			for(const auto& c : line)
			{
				if(num_answers.find(c) == num_answers.end())
					num_answers[c] = 1;
				else
					num_answers[c]++;
			}

			num_people_in_group++;
		}
	}
	std::cout << "Total number of answers: " << total_num_answers << "\n";
}
