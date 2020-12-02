#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<int> input_numbers;

	// task: given N formatted lines like this:
	// X-Y Z: <string>
	// validate if the character Z is at position X *exor* Y, indexed from 1.
	int num_total_matches = 0;

	while(std::getline(input_file, input_line))
	{
		std::stringstream ss(input_line);

		std::string condition_string;
		ss >> condition_string;
		auto split_pos = condition_string.find('-');

		int min_num = std::stoi(condition_string.substr(0, split_pos));
		int max_num = std::stoi(condition_string.substr(split_pos + 1));

		std::string target_string;
		ss >> target_string;

		char target_char = target_string[0];

		std::string match_string;
		ss >> match_string;

		// Check condition - character either at position min or position max.
		bool condition_true = (match_string[min_num - 1] == target_char) ^ (match_string[max_num - 1] == target_char);

		if(condition_true)
		{
			std::cout << "Match found in line: " << input_line << "\n";
			num_total_matches++;
		}
		else
		{
			std::cout << "No match in line: " << input_line << "\n";
		}
	}

	std::cout << "Total number of valid passwords: " << num_total_matches << "\n";
}
