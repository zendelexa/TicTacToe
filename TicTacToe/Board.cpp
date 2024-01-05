#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "Board.h"
#include "Move.h"

const char BLANK_TILE = ' ';
const char TIE_SYMBOL = '-';
const char FORCED_TIE_SYMBOL = '_';

Board::Board(const int board_size, const int players_amount) : 
	board_size(board_size), 
	players_amount(players_amount), 
	board(board_size, std::vector<char>(board_size, BLANK_TILE)), 
	empty_tiles_remaining(board_size * board_size) 
{}

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

void Board::place(const int y, const int x, const int current_player)
{
	if (board[y][x] != BLANK_TILE)
		throw std::invalid_argument("Invalid move. The tile is already occupied.");

	char current_symbol = 'A' + (char)current_player;
	board[y][x] = current_symbol;
	empty_tiles_remaining--;
}

char Board::checkWin() const //TODO: Refactor
{
	int possible_lines = 0;

	// Horizontal lines
	for (int y = 0; y < board_size; y++)
	{
		char winner_symbol = board[y][0];
		char possible_winner = winner_symbol;
		for (int x = 1; x < board_size; x++)
		{
			if (possible_winner == BLANK_TILE)
				possible_winner = board[y][x];

			if (winner_symbol != board[y][x])
			{
				winner_symbol = BLANK_TILE;
				if (possible_winner != BLANK_TILE && board[y][x] != BLANK_TILE)
				{
					possible_winner = TIE_SYMBOL;
					break;
				}
			}
		}
		if (winner_symbol != BLANK_TILE)
			return winner_symbol;
		if (possible_winner != TIE_SYMBOL)
			possible_lines++;
	}

	// Vertical lines
	for (int x = 0; x < board_size; x++)
	{
		char winner_symbol = board[0][x];
		char possible_winner = winner_symbol;
		for (int y = 1; y < board_size; y++)
		{
			if (possible_winner == BLANK_TILE)
				possible_winner = board[y][x];

			if (winner_symbol != board[y][x])
			{
				winner_symbol = BLANK_TILE;
				if (possible_winner != BLANK_TILE && board[y][x] != BLANK_TILE)
				{
					possible_winner = TIE_SYMBOL;
					break;
				}
			}
		}
		if (winner_symbol != BLANK_TILE)
			return winner_symbol;
		if (possible_winner != TIE_SYMBOL)
			possible_lines++;
	}

	// Diagonals
	char winner_symbol = board[0][0];
	char possible_winner = winner_symbol;
	for (int y = 1; y < board_size; y++)
	{
		if (possible_winner == BLANK_TILE)
			possible_winner = board[y][y];

		if (winner_symbol != board[y][y])
		{
			winner_symbol = BLANK_TILE;
			if (possible_winner != BLANK_TILE && board[y][y] != BLANK_TILE)
			{
				possible_winner = TIE_SYMBOL;
				break;
			}
		}
	}
	if (winner_symbol != BLANK_TILE)
		return winner_symbol;
	if (possible_winner != TIE_SYMBOL)
		possible_lines++;

	winner_symbol = board[0][board_size - 1];
	possible_winner = winner_symbol;
	for (int y = 1; y < board_size; y++)
	{
		if (possible_winner == BLANK_TILE)
			possible_winner = board[y][board_size - 1 - y];

		if (winner_symbol != board[y][board_size - 1 - y])
		{
			winner_symbol = BLANK_TILE;
			if (possible_winner != BLANK_TILE && board[y][board_size - 1 - y] != BLANK_TILE)
			{
				possible_winner = TIE_SYMBOL;
				break;
			}
		}
	}
	if (winner_symbol != BLANK_TILE)
		return winner_symbol;
	if (possible_winner != TIE_SYMBOL)
		possible_lines++;

	// Not a win
	if (possible_lines == 0 && empty_tiles_remaining != 0)
		return FORCED_TIE_SYMBOL;
	if (empty_tiles_remaining == 0)
		return TIE_SYMBOL;
	return BLANK_TILE;
}

Move Board::getBestMove(const int current_player)
{
	char current_player_symbol = 'A' + (char)current_player;

	Move best_memoized_move = memoization.getMove(board);
	if (best_memoized_move.has_move)
		return best_memoized_move;

	char outcome = checkWin();
	if (outcome == FORCED_TIE_SYMBOL)
	{
		std::vector<std::pair<int, int>> empty_tiles;
		for (int y = 0; y < board_size; y++)
			for (int x = 0; x < board_size; x++)
				if (board[y][x] == BLANK_TILE)
					empty_tiles.push_back({ y, x });
		int index = rand() % empty_tiles.size();
		Move best_move(empty_tiles[index].first, empty_tiles[index].second, empty_tiles.size(), TIE_SYMBOL);
		memoization.setMove(board, best_move);
		return best_move;
	}
	if (outcome != BLANK_TILE && outcome != TIE_SYMBOL || outcome == TIE_SYMBOL && empty_tiles_remaining == 0)
	{
		Move best_move(outcome);
		memoization.setMove(board, best_move);
		return best_move;
	}

	const char DEFAULT_EVALUATION = '\n'; // Absurd symbol, technically it represents that everyone's losing
	std::vector<Move> best_moves = { Move(DEFAULT_EVALUATION) };
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			if (board[y][x] != BLANK_TILE) continue;

			board[y][x] = current_player_symbol;
			empty_tiles_remaining--;
			
			Move next_move = getBestMove((current_player + 1) % players_amount);
			const Move& best_move = best_moves[0];
			if (best_move.isWorse(next_move, current_player_symbol) || !best_move.has_move)
			{
				best_moves.clear();
				best_moves.push_back(Move(y, x, next_move.moves_remaining + 1, next_move.evaluation));
			}
			else if (best_move.isSame(next_move, current_player_symbol))
			{
				best_moves.push_back(Move(y, x, next_move.moves_remaining + 1, next_move.evaluation));
			}

			board[y][x] = BLANK_TILE;
			empty_tiles_remaining++;
		}
	}

	const Move& best_move = best_moves[rand() % best_moves.size()];
	memoization.setMove(board, best_move);
	return best_move;
}

int Board::emptyTilesRemaining() const
{
	return empty_tiles_remaining;
}
