#pragma once
#include <vector>
#include <map>
#include <string>
#include "Move.h"

class Board
{
	const int board_size;
	std::vector<std::vector<char>> board;
	std::map<std::string, Move> memoization;

public:
	Board(const int board_size);

	void print() const;
	void place(const int y, const int x, char symbol);
	char checkWin() const;
	Move getBestMove(const std::vector<char>& player_sequence, int current_player);
	std::string toString() const;
};

