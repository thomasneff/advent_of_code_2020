#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class TileType
{
	Tree,
	Empty
};

class TreeMap
{
public:
	// This assumes everything about the input is not malformed, there is no error handling at all.
	TreeMap(std::vector<std::string> all_lines_from_file) : width(all_lines_from_file[0].size()), height(all_lines_from_file.size())
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

	void setFromXYChar(char tile, int x, int y)
	{
		TileType t = TileType::Empty;

		if(tile == '#')
			t = TileType::Tree;

		tiles[x + width * y] = t;
	}

	int getHeight() { return height; }

	int getWidth() { return width; }

private:
	std::vector<TileType> tiles;
	int width;
	int height;
};

int task_map_iteration(TreeMap& tree_map, int add_x, int add_y)
{
	int height = tree_map.getHeight();
	int width = tree_map.getWidth();

	int pos_x = 0;
	int pos_y = 0;
	int num_trees = 0;

	while(pos_y < height)
	{
		// Check tree, repeat in x via modulo
		if(tree_map.getFromXY(pos_x % width, pos_y) == TileType::Tree)
			num_trees++;

		// Increase 3 x, 1 y according to task
		pos_x += add_x;
		pos_y += add_y;
	}

	return num_trees;
}

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<std::string> input_lines;

	// task: read 2d map, start top left, go 3 right 1 down each "iteration", check how many trees are hit
	//       map repeats horizontally, end -> when bottom is hit

	// get all input numbers from file
	while(std::getline(input_file, input_line))
	{
		input_lines.push_back(input_line);
	}

	TreeMap tree_map(input_lines);

	// Now we can iterate the tree map according to the algorithm
	int trees_1 = task_map_iteration(tree_map, 1, 1);
	int trees_2 = task_map_iteration(tree_map, 3, 1);
	int trees_3 = task_map_iteration(tree_map, 5, 1);
	int trees_4 = task_map_iteration(tree_map, 7, 1);
	int trees_5 = task_map_iteration(tree_map, 1, 2);
	std::cout << "Number of trees encountered mult: " << trees_1 * trees_2 * trees_3 * trees_4 * trees_5 << "\n";
}
