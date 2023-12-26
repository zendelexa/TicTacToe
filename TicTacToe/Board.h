#pragma once
#include <vector>
#include "Optional.cpp"
#include "Move.h"

class Board
{
	const uint8_t board_size;
	std::vector<std::vector<char>> board;

public:
	Board(const uint8_t board_size);

	void print() const;
	void place(const uint8_t y, const uint8_t x, char symbol);
	char checkWin() const;
	Move getBestMove(const std::vector<char>& player_sequence, uint8_t current_player);
};

