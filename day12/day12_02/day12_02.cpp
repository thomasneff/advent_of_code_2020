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

struct Action
{
	char type;
	int amount;
};

struct IntVector
{
	int x;
	int y;
};

IntVector rotate_by_90(IntVector in)
{
	return IntVector{in.y, -in.x};
}

IntVector rotate_by_90_increments(IntVector in, int angle)
{
	angle = angle % 360;

	if (angle < 0)
		angle = 360 + angle;

	int num_rotates = angle / 90;

	IntVector new_vec = in;
	for (int i = 0; i < num_rotates; i++)
	{
		new_vec = rotate_by_90(new_vec);
	}

	return new_vec;
}

int main()
{
	std::ifstream input_file("input.txt");

	std::string input_line;

	std::vector<Action> input_actions;

	// get all input numbers from file
	while (std::getline(input_file, input_line))
	{
		Action a{input_line[0], std::stoi(input_line.substr(1))};

		std::cout << "Action: " << a.type << a.amount << "\n";

		input_actions.push_back(a);
	}

	// Starting east
	// north/east are positive, south/west are negative
	IntVector ship_position = {0, 0};
	IntVector waypoint_direction = {10, 1};

	for (const auto &action : input_actions)
	{
		if (action.type == 'N')
		{
			waypoint_direction.y += action.amount;
		}
		else if (action.type == 'S')
		{
			waypoint_direction.y -= action.amount;
		}
		else if (action.type == 'E')
		{
			waypoint_direction.x += action.amount;
		}
		else if (action.type == 'W')
		{
			waypoint_direction.x -= action.amount;
		}
		else if (action.type == 'L')
		{
			waypoint_direction = rotate_by_90_increments(waypoint_direction, -action.amount);
		}
		else if (action.type == 'R')
		{
			waypoint_direction = rotate_by_90_increments(waypoint_direction, action.amount);
		}
		else if (action.type == 'F')
		{
			ship_position.x += waypoint_direction.x * action.amount;
			ship_position.y += waypoint_direction.y * action.amount;
		}

		std::cout << "Ship position: " << ship_position.x << "," << ship_position.y << "\n";
		std::cout << "waypoint direction: " << waypoint_direction.x << ", " << waypoint_direction.y << "\n";
	}

	std::cout << "Manhattan distance:" << std::abs(ship_position.x) + std::abs(ship_position.y) << "\n";
}
