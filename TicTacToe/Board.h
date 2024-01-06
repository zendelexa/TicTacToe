#pragma once
#include <vector>
#include <map>
#include <string>
#include "Move.h"
#include "MoveMap.h"
#include "BoardLine.h"

class Board
{
	int board_size;
	int players_amount;
	std::vector<std::vector<char>> board;
	MoveMap memoization;
	int empty_tiles_remaining;
	std::vector<BoardLine> lines;

public:

	Board(int board_size, int players_amount);

	void print() const;
	void place(int y, int x, int current_player);
	char checkWin() const;
	Move getBestMove(int current_player);
	int emptyTilesRemaining() const;
};

