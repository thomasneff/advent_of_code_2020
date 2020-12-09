#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

bool contains_sum(const std::vector<long long>& input_numbers, int subarray_start, int subarray_end, long long target)
{
	// get new subarray

	std::vector<long long> input_part;

	for(int i = subarray_start; i < subarray_end; i++)
	{
		input_part.push_back(input_numbers[i]);
	}

	std::sort(input_part.begin(), input_part.end());

	int start = 0;
	int end = input_part.size() - 1;

	while(end > start)
	{
		// check if sum is bigger or smaller than target
		long long sum = input_part[start] + input_part[end];

		if(sum > target)
			end--;
		else if(sum < target)
			start++;
		else
		{
			// found it!
			std::cout << "Found 2 elements that add to " << target << ": " << input_part[start] << " + " << input_part[end] << " = "
			          << input_part[start] + input_part[end] << "\n";
			return true;
		}
	}
	return false;
}

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<std::string> input_lines;

	std::vector<long long> input_numbers;

	// get all input numbers from file
	while(std::getline(input_file, input_line))
	{
		std::cout << "input line: " << input_line << "\n";
		std::cout << "int: " << std::stoll(input_line) << "\n";
		input_numbers.push_back(std::stoll(input_line));
	}

	long long element_with_condition = 0;

	for(size_t i = 0; i < input_numbers.size() - 25 - 1; i++)
	{
		if(!contains_sum(input_numbers, i, i + 25, input_numbers[i + 25]))
		{
			std::cout << "Element which is not the sum of any of the previous 25 elements: " << input_numbers[i + 25] << "\n";

			element_with_condition = input_numbers[i + 25];

			std::cout << "Check: \n";

			for(size_t j = i; j < i + 25; j++)
			{
				std::cout << input_numbers[j] << "\n";
			}
			break;
		}
	}


	// Task 2: find a contiguous range which sums to element_with_condition, then report min and max

	size_t start = 0;
	size_t end = 0;
	long long sum = input_numbers[0];

	while(end < input_numbers.size()) 
	{
		if(sum < element_with_condition)
		{
			// If the current sum is smaller, we increase the end pointer and add to the sum
			end++;
			sum += input_numbers[end];
		}
		else if (sum > element_with_condition)
		{
			// If the current sum is larger, we increase the start pointer and subtract from the sum
			sum -= input_numbers[start];
			start++;
		}
		else 
		{
			// We found it!
			std::cout << "Found contiguous range that sums to " << element_with_condition << " ( " << start << " - " << end << ")\n";

			long long min = std::numeric_limits<long long>::max();
			long long max = -1;

			for(size_t i = start; i <= end; i++)
			{
				min = std::min(input_numbers[i], min);
				max = std::max(input_numbers[i], max);
			}

			// Result
			std::cout << "Result: " << min << " + " << max << " = " << min + max << "\n";
			break;
		}
	}

}
