#include "Board.h"
#include "BoardEvaluation.h"
#include <vector>
#include <iostream>

const char BLANK_TILE = ' ';

Board::Board(const uint8_t board_size) : board_size(board_size), board(board_size, std::vector<char>(board_size, BLANK_TILE)) {}

void Board::print() const
{
	for (uint8_t y = 0; y < board_size; y++)
	{
		if (y != 0)
		{
			std::cout << std::endl << "-";
			for (uint8_t x = 1; x < board_size; x++)
				std::cout << "--";
			std::cout << std::endl;
		}

		for (uint8_t x = 0; x < board_size; x++)
		{
			if (x != 0)
				std::cout << "|";
			std::cout << board[y][x];
		}
	}
	std::cout << std::endl;
}

void Board::place(const uint8_t y, const uint8_t x, char symbol)
{
	board[y][x] = symbol;
}

char Board::checkWin() const
{
	// Horizontal lines
	for (uint8_t y = 0; y < board_size; y++)
	{
		char winner_symbol = board[y][0];
		for (uint8_t x = 1; x < board_size; x++)
		{
			if (winner_symbol != board[y][x])
			{
				winner_symbol = BLANK_TILE;
				break;
			}
		}
		if (winner_symbol != BLANK_TILE)
			return winner_symbol;
	}

	// Vertical lines
	for (uint8_t x = 0; x < board_size; x++)
	{
		char winner_symbol = board[0][x];
		for (uint8_t y = 1; y < board_size; y++)
		{
			if (winner_symbol != board[y][x])
			{
				winner_symbol = BLANK_TILE;
				break;
			}
		}
		if (winner_symbol != BLANK_TILE)
			return winner_symbol;
	}

	// Diagonals
	char winner_symbol = board[0][0];
	for (uint8_t y = 1; y < board_size; y++)
	{
		if (winner_symbol != board[y][y])
		{
			winner_symbol = BLANK_TILE;
			break;
		}
	}
	if (winner_symbol != BLANK_TILE)
		return winner_symbol;

	winner_symbol = board[0][board_size - 1];
	for (uint8_t y = 1; y < board_size; y++)
	{
		if (winner_symbol != board[y][board_size - 1 - y])
		{
			winner_symbol = BLANK_TILE;
			break;
		}
	}
	if (winner_symbol != BLANK_TILE)
		return winner_symbol;

	// Not a win
	return BLANK_TILE;
}