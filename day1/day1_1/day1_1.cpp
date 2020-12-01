#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<int> input_numbers;

	// get all input numbers from file
	while(std::getline(input_file, input_line))
	{
		input_numbers.push_back(std::stoi(input_line));
	}

	// task day 1/1: find 2 numbers that add to 2020, return product of them
	// brute force is much simpler, but we can also sort the array and then use two pointers to get to the solution
	// and it's more fun :)

	// sort ascending
	std::sort(input_numbers.begin(), input_numbers.end());

	int start = 0;
	int end = input_numbers.size() - 1;
	const int target = 2020;

	while(end > start)
	{
		// check if sum is bigger or smaller than 2020
		int sum = input_numbers[start] + input_numbers[end];

		if(sum > target)
			end--;
		else if(sum < target)
			start++;
		else
		{
			// found it!
			std::cout << "Found 2 elements that add to " << target << ": " << input_numbers[start] << " * " << input_numbers[end] << " = "
			          << input_numbers[start] * input_numbers[end] << "\n";
			break;
		}
	}
}
