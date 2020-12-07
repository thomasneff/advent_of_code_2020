#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
struct BagType
{
	std::string type_string;
	int number_of_bags;
};

struct BagContainer
{
	std::string type;
	std::vector<BagType> children;
	std::set<std::string> parents;
};

std::string get_main_bag_type(const std::string& line)
{
	// split line by "contain"
	auto contain_location = line.find("contain");
	std::string bag_container = line.substr(0, contain_location);

	// <type> always consists of 2 words separated by spaces
	std::stringstream ss(bag_container);

	// those variable names suck, but eh
	std::string first_part;
	std::string second_part;
	ss >> first_part;
	ss >> second_part;

	return first_part + " " + second_part;
}

std::vector<BagType> get_children(const std::string& line)
{
	std::vector<BagType> ret;

	auto contain_location = line.find("contain");
	std::string bag_children = line.substr(contain_location + 7); // 7 chars for "contain"

	// Check if we can find a comma
	size_t previous_location = 0;
	std::string current_string = bag_children;
	while(true)
	{
		current_string = current_string.substr(previous_location);
		auto comma_location = current_string.find(',');

		if(comma_location == std::string::npos)
		{
			// final parse, get child from stringstream parsing
			std::stringstream ss(current_string);
			std::string first_part;
			std::string second_part;
			std::string third_part;

			ss >> first_part;
			ss >> second_part;
			ss >> third_part;

			if(first_part != "no")
			{
				BagType t;
				t.number_of_bags = std::stoi(first_part);
				t.type_string = second_part + " " + third_part;
				ret.push_back(t);
			}

			break;
		}
		else
		{
			// not final parse
			// final parse, get child from stringstream parsing
			std::stringstream ss(current_string.substr(0, comma_location));
			std::string first_part;
			std::string second_part;
			std::string third_part;

			ss >> first_part;
			ss >> second_part;
			ss >> third_part;

			BagType t;
			t.number_of_bags = std::stoi(first_part);
			t.type_string = second_part + " " + third_part;

			ret.push_back(t);
		}

		previous_location = comma_location + 1;
	}

	return ret;
}

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

	// task: lines are structured as follows:
	// <type> bag(s) contain <num> <type> bag(s)
	// we need to parse it into conditions -> hold a map from <type> to <num, type>
	// then we can iterate and check for "shiny gold" as the type, for which we need to find all possible containers

	std::unordered_map<std::string, BagContainer> bag_map;

	for(const auto& line : input_lines)
	{
		// parse children
		// they are either formatted as "no other" or <num> <type> bags

		std::string cont_type = get_main_bag_type(line);

		auto& cont = bag_map[cont_type];
		cont.type = cont_type;
		cont.children = get_children(line);

		for(auto& child : cont.children)
		{
			// Set parents if they exist in the map

			auto& test = bag_map[child.type_string];
			bag_map[child.type_string].parents.insert(cont.type);

			if(child.type_string == "shiny gold")
			{
				auto& test = bag_map[child.type_string];
				int a = 3;
			}
		}
	}

	// After we did all that, we start by going to the "shiny gold" entry in the map and iterate through all parents and count the number

	std::deque<BagContainer> nodes_to_process;
	nodes_to_process.push_back(bag_map["shiny gold"]);

	std::set<std::string> bag_types_that_contain_shiny_gold;

	auto test = bag_map["plaid purple"];

	while(nodes_to_process.empty() == false)
	{
		// get new node
		auto current_node = nodes_to_process.front();
		nodes_to_process.pop_front();

		// add the element to a set of potential bags that can contain our target
		bag_types_that_contain_shiny_gold.insert(current_node.type);

		for(const auto& parent : current_node.parents)
		{
			nodes_to_process.push_back(bag_map[parent]);
		}
	}

	// Total number of entries in set (-1 because shiny gold was in them too) is our number.
	std::cout << "Total number of bag types that could contain shiny gold: " << bag_types_that_contain_shiny_gold.size() - 1 << "\n";
}
