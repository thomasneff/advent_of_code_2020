#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int get_seat_id(const std::string& line)
{
	// get seat id for a given line/boarding pass
	int seat_row = 0;
	int seat_col = 0;
	int num_rows = 128;
	int num_cols = 8;
	int rows_min = 0;
	int rows_max = num_rows - 1;
	int cols_max = num_cols - 1;
	int cols_min = 0;

	// 7 characters for row positioning
	for(int i = 0; i < 7; i++)
	{
		int space_range = rows_max - rows_min;
		if(line[i] == 'F')
		{
			rows_max -= (space_range / 2) + 1;
		}
		else if(line[i] == 'B')
		{
			rows_min += (space_range / 2) + 1;
		}
	}

	seat_row = rows_min;

	// 3 characters for row positioning
	for(int i = 7; i < 10; i++)
	{
		int space_range = cols_max - cols_min;
		if(line[i] == 'L')
		{
			cols_max -= (space_range / 2) + 1;
		}
		else if(line[i] == 'R')
		{
			cols_min += (space_range / 2) + 1;
		}
	}

	seat_col = cols_min;

	return seat_row * 8 + seat_col;
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

	// First 7 characters either F or B for space partitioning of 128 rows.
	// followed by 3 characters L/R for space partitioning of 8 columns.
	// return highest id (row * 8 + col)

	// test example
	// get_seat_id("BFFFBBFRRR");

	int max_seat_id = -1;
	for(const auto& line : input_lines)
	{
		max_seat_id = std::max(get_seat_id(line), max_seat_id);
	}
	std::cout << "Max seat id: " << max_seat_id << "\n";
}
