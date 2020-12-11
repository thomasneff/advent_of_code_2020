#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class TileType
{
	Floor,
	EmptySeat,
	OccupiedSeat
};

class SeatMap
{
public:
	// This assumes everything about the input is not malformed, there is no error handling at all.
	SeatMap(std::vector<std::string> all_lines_from_file) : width(all_lines_from_file[0].size()), height(all_lines_from_file.size())
	{
		// allocate vector from width and height
		tiles.resize(width * height);

		// copy elements into map

		for(int y = 0; y < height; y++)
		{
			const auto& line = all_lines_from_file[y];
			for(int x = 0; x < width; x++)
			{
				setFromXYChar(line[x], x, y);
			}
		}
	}

	TileType getFromXY(int x, int y) { return tiles[x + width * y]; }

	void setFromXY(TileType tile, int x, int y) { tiles[x + width * y] = tile; }

	void setFromXYChar(char tile, int x, int y)
	{
		TileType t = TileType::Floor;

		if(tile == 'L')
			t = TileType::EmptySeat;
		else if(tile == '#')
			t = TileType::OccupiedSeat;

		tiles[x + width * y] = t;
	}

	int getHeight() { return height; }

	int getWidth() { return width; }

	int getNumberOfOccupiedVisibleSeats(int x, int y)
	{
		int num_occupied = 0;
		// check neighbors
		for(int x_off = -1; x_off <= 1; x_off++)
		{
			for(int y_off = -1; y_off <= 1; y_off++)
			{
				// Don't check self
				if(x_off == 0 && y_off == 0)
					continue;

				// change: we go in the direction until we find a non-floor tile
				int x_neighbor = x;
				int y_neighbor = y;
				TileType visible_tile = TileType::Floor;

				while(visible_tile == TileType::Floor)
				{
					x_neighbor += x_off;
					y_neighbor += y_off;
					if(x_neighbor < 0 || x_neighbor >= width)
						break;

					if(y_neighbor < 0 || y_neighbor >= height)
						break;

					visible_tile = getFromXY(x_neighbor, y_neighbor);
				}

				if(visible_tile == TileType::OccupiedSeat)
				{
					num_occupied++;
				}
			}
		}

		return num_occupied;
	}

	TileType ruleBasedChange(int x, int y)
	{
		// 1.) if a seat is empty and there are no occupied seats in any direction (first hit only), the seat becomes occupied
		// 2.) if a seat is occupied and five or more seats in any direction (first hit only) to it are also occupied, the seat becomes empty
		// 3.) otherwise, the seat's state does not change.
		TileType t = getFromXY(x, y);

		if(t == TileType::EmptySeat)
		{
			int num_occupied = getNumberOfOccupiedVisibleSeats(x, y);
			if(num_occupied == 0)
				t = TileType::OccupiedSeat;
		}
		else if(t == TileType::OccupiedSeat)
		{
			int num_occupied = getNumberOfOccupiedVisibleSeats(x, y);
			if(num_occupied >= 5)
				t = TileType::EmptySeat;
		}

		return t;
	}

	char getCharFromTile(TileType t)
	{
		if(t == TileType::EmptySeat)
			return 'L';
		else if(t == TileType::Floor)
			return '.';
		else if(t == TileType::OccupiedSeat)
			return '#';

		return '.';
	}

	int getOccupiedCount()
	{
		int num_occupied = 0;

		for(const auto& t : tiles)
		{
			if(t == TileType::OccupiedSeat)
				num_occupied++;
		}

		return num_occupied;
	}

	void printField()
	{
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				std::cout << getCharFromTile(getFromXY(x, y));
			}

			std::cout << "\n";
		}
	}

	bool simulateStep()
	{
		// Simulate a step:

		// First: copy the game state / tiles
		// default copy ctor is fine here
		SeatMap map_copy = *this;
		int num_changes = 0;

		std::cout << "---------------------\n";
		std::cout << "Simulating step: \n";
		// printField();

		for(int x = 0; x < width; x++)
		{
			for(int y = 0; y < height; y++)
			{
				// for each tile, check its conditions
				TileType new_tile = map_copy.ruleBasedChange(x, y);

				if(new_tile != getFromXY(x, y))
				{
					num_changes++;
				}

				setFromXY(new_tile, x, y);
			}
		}

		std::cout << "Num changes: " << num_changes << "\n";

		return num_changes != 0;
	}

private:
	std::vector<TileType> tiles;
	int width;
	int height;
};

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<std::string> input_lines;

	// task: read 2d map and simulate something akin to cellular automata / conway's game of life

	// get all input numbers from file
	while(std::getline(input_file, input_line))
	{
		input_lines.push_back(input_line);
	}

	SeatMap seat_map(input_lines);

	while(seat_map.simulateStep())
		;

	std::cout << "Done - Number of occupied seats: " << seat_map.getOccupiedCount() << "\n";
}
