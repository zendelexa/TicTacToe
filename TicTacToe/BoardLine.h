#pragma once
#include <vector>


class BoardLine
{
	int start_y;
	int start_x;
	int dy;
	int dx;
	int total_steps;

public:
	BoardLine(int start_y, int start_x, int dy, int dx, int total_steps);

	char getTile(const std::vector<std::vector<char>>& board, int steps) const;
	bool isWin(const std::vector<std::vector<char>>& board) const;
	bool isPossibleWin(const std::vector<std::vector<char>>& board) const;
};