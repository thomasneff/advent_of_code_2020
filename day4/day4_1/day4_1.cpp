#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
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

	std::map<std::string, std::string> current_map;
	std::vector<std::string> required_entries = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
	std::vector<std::string> all_entry_types = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

	bool passport_invalid = false;
	int num_valid_passports = 0;
	int line_count = -1;
	for(const auto& line : input_lines)
	{
		if(line.empty())
		{
			if(!passport_invalid)
			{
				// validate current passport and clear:
				for(const auto& pair : current_map)
				{
					if(std::find(all_entry_types.begin(), all_entry_types.end(), pair.first) == all_entry_types.end())
					{
						// invalid entry type, invalid passport
						passport_invalid = true;
						break;
					}
				}
			}
			// Check if all elements are contained inside the passport

			if(!passport_invalid)
			{
				for(const auto& required_entry : required_entries)
				{
					if(current_map.find(required_entry) == current_map.end())
					{
						passport_invalid = true;
						break;
					}
				}
			}

			if(passport_invalid == false)
			{
				num_valid_passports++;
			}
			else
			{
				std::cout << "invalid passport: ";
				for(const auto& pair : current_map)
				{
					std::cout << pair.first << ":" << pair.second << " ";
				}
				std::cout << "\n";
			}
			passport_invalid = false;

			current_map.clear();
		}
		else
		{
			// split into tokens based on spaces and colons

			std::stringstream ss(line);

			while(ss)
			{
				std::string key_value_string;
				ss >> key_value_string;

				if(key_value_string.empty())
					break;

				auto colon_pos = key_value_string.find(':');

				std::string key = key_value_string.substr(0, colon_pos);
				std::string value = key_value_string.substr(colon_pos + 1);

				if(current_map.find(key) != current_map.end())
				{
					// duplicate key entry - invalid (I guess?)
					passport_invalid = true;
					break;
				}

				current_map[key] = value;
			}
		}
	}

	std::cout << "number of valid passports: " << num_valid_passports << "\n";
}
