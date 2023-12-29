#include "Board.h"
#include <vector>
#include <iostream>
#include "Optional.cpp"
#include "Move.h"

const char BLANK_TILE = ' ';
const char TIE_SYMBOL = '-';

Board::Board(const int board_size) : board_size(board_size), board(board_size, std::vector<char>(board_size, BLANK_TILE)) {}

void Board::print() const
{
	for (int y = 0; y < board_size; y++)
	{
		if (y != 0)
		{
			std::cout << std::endl << "-";
			for (int x = 1; x < board_size; x++)
				std::cout << "--";
			std::cout << std::endl;
		}

		for (int x = 0; x < board_size; x++)
		{
			if (x != 0)
				std::cout << "|";
			std::cout << board[y][x];
		}
	}
	std::cout << std::endl;
}

void Board::place(const int y, const int x, char symbol)
{
	board[y][x] = symbol;
}

char Board::checkWin() const
{
	// Horizontal lines
	for (int y = 0; y < board_size; y++)
	{
		char winner_symbol = board[y][0];
		for (int x = 1; x < board_size; x++)
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
	for (int x = 0; x < board_size; x++)
	{
		char winner_symbol = board[0][x];
		for (int y = 1; y < board_size; y++)
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
	for (int y = 1; y < board_size; y++)
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
	for (int y = 1; y < board_size; y++)
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
	for (auto& row : board)
		for (auto& tile : row)
			if (tile == BLANK_TILE)
				return BLANK_TILE;
	return TIE_SYMBOL;
}

Move Board::getBestMove(const std::vector<char>& player_sequence, int current_player)
{
	char outcome = checkWin();
	if (outcome == TIE_SYMBOL)
	{
		return Move(player_sequence.size(), 0);
	}
	if (outcome != BLANK_TILE)
	{
		int previous_player = (current_player + player_sequence.size() - 1) % player_sequence.size();
		int winning_player = previous_player;
		Move move(player_sequence.size(), -1);
		move.evaluation[winning_player] = 1;
		return move;
	}

	Move best_move(player_sequence.size(), -1);
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			if (board[y][x] != BLANK_TILE) continue;

			board[y][x] = player_sequence[current_player];
			
			Move next_move = getBestMove(player_sequence, (current_player + 1) % player_sequence.size());
			if (best_move.isWorse(next_move, current_player) || !best_move.has_move)
			{
				best_move.has_move = true;
				best_move.evaluation = next_move.evaluation;
				best_move.y = y;
				best_move.x = x;
			}
			/*else if (best_move.isSame(next_move, current_player))
			{
				for (int i = 0; i < best_move.evaluation.size(); i++)
				{
					best_move.evaluation[i] += next_move.evaluation[i];
				}
			}*/

			board[y][x] = BLANK_TILE;
		}
	}
	return best_move;
}