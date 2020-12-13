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

long long intpow(long long x, long long y, long long m)
{
	if (y == 0)
		return 1;

	long long ret = 1;

	for (int i = 1; i <= y; i++)
		ret = (ret * x) % m;

	return ret % m;
}

long long inv(long long a, long long m)
{
	// Return modulo inverse via fermat's little theorem because our m's are primes
	return intpow(a, m - 2, m);
}

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	int earliest_time = 0;
	std::vector<long long> bus_ids;
	std::vector<long long> offsets;

	// get all input numbers from file
	std::getline(input_file, input_line);
	earliest_time = std::stoi(input_line);

	long long offset = 0;

	while (std::getline(input_file, input_line, ','))
	{
		//std::cout << input_line << "\n";
		try
		{
			bus_ids.push_back(std::stoll(input_line));
			offsets.push_back(-(((offset)-bus_ids.back()) % bus_ids.back()));
		}
		catch (const std::exception &e)
		{
		}

		offset++;
	}

	// print bus ids
	std::cout << "Bus ids / offsets:\n";
	for (int i = 0; i < bus_ids.size(); i++)
	{
		std::cout << bus_ids[i] << " / " << offsets[i] << "\n";
	}

	// This is a case for the Chinese Remainder Theorem

	long long M = 1;

	for (const auto &bus_id : bus_ids)
		M *= bus_id;

	std::cout << "M: " << M << "\n";

	std::vector<long long> m;

	long long Y = 0;

	for (int i = 0; i < bus_ids.size(); i++)
	{
		long long m_prime = M / bus_ids[i];
		Y += offsets[i] * inv(m_prime, bus_ids[i]) * m_prime;
	}

	std::cout << "Final Y: " << Y % M << std::endl;
}
