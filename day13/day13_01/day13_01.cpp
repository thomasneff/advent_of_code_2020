#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	int earliest_time = 0;
	std::vector<int> bus_ids;

	// get all input numbers from file
	std::getline(input_file, input_line);
	earliest_time = std::stoi(input_line);

	while (std::getline(input_file, input_line, ','))
	{
		//std::cout << input_line << "\n";
		try
		{
			bus_ids.push_back(std::stoi(input_line));
		}
		catch (const std::exception &e)
		{
		}
	}

	// print bus ids
	std::cout << "Bus ids:\n";
	for (const auto &bus_id : bus_ids)
	{
		std::cout << bus_id << "\n";
	}

	// For each bus id, check the modulo and get the minimum?
	int min_wait_time = std::numeric_limits<int>::max();
	int best_bus = -1;
	for (int i = 0; i < bus_ids.size(); i++)
	{
		int bus_id = bus_ids[i];
		int wait_time = bus_id - (earliest_time % bus_id);

		if (wait_time < min_wait_time)
		{
			min_wait_time = wait_time;
			best_bus = bus_id;
		}
	}

	std::cout << "Target: " << earliest_time << ", Best bus: " << best_bus << " * wait time " << min_wait_time << " = " << best_bus * min_wait_time << "\n";
}
