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
	// validate if the character Z is inside <string> between X and Y times, and return the number of valid "passwords"
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

		int num_matches = 0;

		for(const auto match_char : match_string)
		{
			if(match_char == target_char)
			{
				num_matches++;
			}
		}

		if(num_matches >= min_num && num_matches <= max_num)
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
