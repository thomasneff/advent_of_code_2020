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

	// sort

	std::sort(input_numbers.begin(), input_numbers.end());

	// start from zero
	long long current_joltage = 0;

	// iterate through all elements and count the differences, max can be 3
	std::vector<long long> difference_count(4);

	for(const auto num : input_numbers)
	{
		auto joltage_diff = num - current_joltage;

		if (joltage_diff > 3 || joltage_diff == 0)
		{
			throw std::runtime_error("Error: joltage difference greater than 3 or equal to 0!");
		}

		difference_count[joltage_diff]++;
		current_joltage = num;
	}

	// Finally, add an additional 3 because the last adapter has a difference of 3
	difference_count[3]++;

	std::cout << "Number of 1 diffs " << difference_count[1] << " * number of 3 diffs " << difference_count[3] << " = " << difference_count[1] * difference_count[3] << "\n";

}
