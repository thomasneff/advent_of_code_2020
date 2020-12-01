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

	// task day 1/2: find 3 numbers that add to 2020, return product of them
	// brute force would require going through all combinations...
	// we could just sort, and then, for a given middle index, do what we did for task1 with 2 pointers.

	// sort ascending
	std::sort(input_numbers.begin(), input_numbers.end());

	int middle = 1;
	const int target = 2020;

	for(int middle = 1; middle < input_numbers.size() - 1; middle++)
	{
		// for each middle index, we split the array into 2 halves and look for the sum of start, middle, end
		// where start goes up to middle - 1 and end goes down to middle + 1

		int start = 0;
		int end = input_numbers.size() - 1;

		while(end > start && start < middle && end > middle)
		{
			// check if sum is bigger or smaller than 2020
			int sum = input_numbers[start] + input_numbers[middle] + input_numbers[end];

			if(sum > target)
				end--;
			else if(sum < target)
				start++;
			else
			{
				// found it!
				std::cout << "Found 3 elements that add to " << target << ": " << input_numbers[start] << " * " << input_numbers[middle] << " * " << input_numbers[end] << " = "
				          << input_numbers[start] * input_numbers[middle] * input_numbers[end] << "\n";
				break;
			}
		}
	}
}
