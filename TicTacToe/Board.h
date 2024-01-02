#pragma once
#include <vector>
#include <map>
#include <string>
#include "Move.h"
#include "MoveMap.h"

class Board
{
	const int board_size;
	const int players_amount;
	std::vector<std::vector<char>> board;
	MoveMap memoization;

public:
	Board(const int board_size, const int players_amount);

	void print() const;
	void place(const int y, const int x, const int current_player);
	char checkWin() const;
	Move getBestMove(const int current_player);
};

