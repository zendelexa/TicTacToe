#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "Board.h"
#include "Move.h"

const char BLANK_TILE = ' ';
const char TIE_SYMBOL = '-';
const char FORCED_TIE_SYMBOL = '_';
const char GAME_STILL_GOING_SYMBOL = BLANK_TILE;


Board::Board(int board_size, int players_amount)
: 
	board_size(board_size), 
	players_amount(players_amount), 
	board(board_size, std::vector<char>(board_size, BLANK_TILE)), 
	empty_tiles_remaining(board_size * board_size) 
{
	for (int i = 0; i < board_size; i++)
	{
		lines.push_back(BoardLine(i, 0, 0, 1, board_size)); // Horizontal line
		lines.push_back(BoardLine(0, i, 1, 0, board_size)); // Vertical line
	}
	lines.push_back(BoardLine(0, 0, 1, 1, board_size)); // Main diagonal
	lines.push_back(BoardLine(0, board_size - 1, 1, -1, board_size)); // Secondary diagonal
}

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

void Board::place(int y, int x, int current_player)
{
	if (board[y][x] != BLANK_TILE)
		throw std::invalid_argument("Invalid move. The tile is already occupied.");

	char current_symbol = 'A' + (char)current_player;
	board[y][x] = current_symbol;
	empty_tiles_remaining--;
}

char Board::checkWin() const
{
	bool is_possible_win = false;

	for (const auto& line : lines)
	{
		if (line.isWin(board))
			return line.getTile(board, 0);

		if (line.isPossibleWin(board))
			is_possible_win = true;
	}

	bool is_end_of_game = empty_tiles_remaining == 0;
	if (is_end_of_game)
		return TIE_SYMBOL;

	if (!is_possible_win)
		return FORCED_TIE_SYMBOL;

	return GAME_STILL_GOING_SYMBOL;
}

std::pair<int, int> getRandomEmptyTile(const std::vector<std::vector<char>>& board)
{
	int board_size = board.size();

	std::vector<std::pair<int, int>> empty_tiles;
	for (int y = 0; y < board_size; y++)
		for (int x = 0; x < board_size; x++)
			if (board[y][x] == BLANK_TILE)
				empty_tiles.push_back({ y, x });
	return empty_tiles[rand() % empty_tiles.size()];
}

Move Board::getBestMove(int current_player)
{
	char current_player_symbol = 'A' + (char)current_player;

	Move best_memoized_move = memoization.getMove(board);
	if (best_memoized_move.has_move)
		return best_memoized_move;

	char outcome = checkWin();
	if (outcome == FORCED_TIE_SYMBOL)
	{
		auto random_empty_tile = getRandomEmptyTile(board);
		Move best_move(random_empty_tile.first, random_empty_tile.second, empty_tiles_remaining - 1, TIE_SYMBOL);
		memoization.setMove(board, best_move);
		return best_move;
	}
	if (outcome != GAME_STILL_GOING_SYMBOL)
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
