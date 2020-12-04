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
	std::vector<std::string> eye_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

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

					// check validity conditions
					if(pair.first == "byr")
					{
						if(pair.second.length() != 4)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}

						int num = std::stoi(pair.second);
						if(num < 1920 || num > 2002)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}
					}
					else if(pair.first == "iyr")
					{
						if(pair.second.length() != 4)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}

						int num = std::stoi(pair.second);
						if(num < 2010 || num > 2020)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}
					}
					else if(pair.first == "eyr")
					{
						if(pair.second.length() != 4)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}

						int num = std::stoi(pair.second);
						if(num < 2020 || num > 2030)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}
					}
					else if(pair.first == "hgt")
					{
						// find cm or in
						auto cm_pos = pair.second.find("cm");
						auto in_pos = pair.second.find("in");

						if(cm_pos != std::string::npos)
						{
							// check first 3 numbers
							int num = std::stoi(pair.second.substr(0, cm_pos));

							if(num < 150 || num > 193)
							{
								passport_invalid = true;
								// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
								break;
							}
						}
						else if(in_pos != std::string::npos)
						{
							// check first 3 numbers
							int num = std::stoi(pair.second.substr(0, in_pos));

							if(num < 59 || num > 76)
							{
								passport_invalid = true;
								// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
								break;
							}
						}
						else
						{
							// didn't find either cm or in, invalid
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}
					}
					else if(pair.first == "hcl")
					{
						if(pair.second.length() != 7)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}

						if(pair.second[0] != '#')
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}

						for(int i = 1; i < 7; i++)
						{
							if(!(pair.second[i] >= 'a' && pair.second[i] <= 'f'))
							{
								if(!(pair.second[i] >= '0' && pair.second[i] <= '9'))
								{
									passport_invalid = true;
									// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
									break;
								}
							}
						}
					}
					else if(pair.first == "ecl")
					{
						if(pair.second.length() != 3)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}

						if(std::find(eye_colors.begin(), eye_colors.end(), pair.second) == eye_colors.end())
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}
					}
					else if(pair.first == "pid")
					{
						if(pair.second.length() != 9)
						{
							passport_invalid = true;
							// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
							break;
						}

						for(const auto& c : pair.second)
						{
							if(c < '0' || c > '9')
							{
								passport_invalid = true;
								// std::cout << "invalid: " << pair.first << ":" << pair.second << "\n";
								break;
							}
						}
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
