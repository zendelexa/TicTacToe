#include "BoardLine.h"

const char BLANK_TILE = ' ';

BoardLine::BoardLine(int start_y, int start_x, int dy, int dx, int total_steps)
:
	start_y(start_y), 
	start_x(start_x),
	dy(dy),
	dx(dx),
	total_steps(total_steps)
{}

char BoardLine::getTile(const std::vector<std::vector<char>>&board, int steps) const
{
	int y = start_y + dy * steps;
	int x = start_x + dx * steps;
	return board[y][x];
}

bool BoardLine::isWin(const std::vector<std::vector<char>>& board) const
{
	char current_winner = getTile(board, 0);

	for (int steps = 0; steps < total_steps; steps++)
	{
		char current_tile = getTile(board, steps);

		if (current_tile == BLANK_TILE)
			return false;
		if (current_tile != current_winner)
			return false;
	}
	return true;
}

bool BoardLine::isPossibleWin(const std::vector<std::vector<char>>& board) const
{
	char possible_winner = BLANK_TILE;
	for (int steps = 0; steps < total_steps; steps++)
	{
		char current_tile = getTile(board, steps);
		if (current_tile == BLANK_TILE) continue;

		bool seen_only_blank_tiles = possible_winner == BLANK_TILE;
		if (seen_only_blank_tiles)
			possible_winner = current_tile;

		bool has_several_players = current_tile != possible_winner;
		if (has_several_players)
			return false;
	}
	return true;
}
