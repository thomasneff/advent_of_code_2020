#include <algorithm>
#include <deque>
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

	std::vector<long long> input_numbers;

	// get all input numbers from file
	while(std::getline(input_file, input_line))
	{
		input_numbers.push_back(std::stoll(input_line));
	}

	// we also add the 0 in front to make things easier
	input_numbers.push_back(0);

	std::sort(input_numbers.begin(), input_numbers.end());

	// count all the permutations where we can reach the end
	// we do this by storing memory for all potential paths that fulfill the condition
	// first we add the target to the array to make things simpler 
	input_numbers.push_back(input_numbers.back() + 3);

	std::vector<long long> valid_paths(input_numbers.size());

	valid_paths[0] = 1;

	for(size_t i = 0; i < input_numbers.size(); i++)
	{
		// go forward until the condition doesn't match anymore
		for(size_t j = i + 1; j < input_numbers.size(); j++)
		{
			if (input_numbers[j] - input_numbers[i] <= 3)
			{
				valid_paths[j]+=valid_paths[i];
			}
			else
			{
				break;
			}
		}
	}

	std::cout << "Number of permutations: " << valid_paths.back() << "\n";
}
