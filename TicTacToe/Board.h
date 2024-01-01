#pragma once
#include <vector>
#include <map>
#include <string>
#include "Move.h"

class Board
{
	const int board_size;
	const int players_amount;
	std::vector<std::vector<char>> board;
	std::map<std::string, Move> memoization;

public:
	Board(const int board_size, const int players_amount);

	void print() const;
	void place(const int y, const int x, const int current_player);
	char checkWin() const;
	Move getBestMove(const int current_player);
	std::string toString() const;
};

