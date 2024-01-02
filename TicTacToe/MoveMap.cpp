#include "MoveMap.h"

std::string toString(const std::vector<std::vector<char>>& board)
{
	std::string res = "";
	for (auto& row : board)
		for (auto& c : row)
			res += c;
	return res;
}

void rotate(std::vector<std::vector<char>>& board)
{
	const int board_size = board.size();
	for (int y = 0; y < board_size / 2; y++)
	{
		for (int x = y; x <= board_size / 2; x++)
		{
			char tmp = board[y][x];
			for (int i = 0; i < 4; i++)
			{
				x = board_size - 1 - x;
				std::swap(x, y);
				std::swap(tmp, board[y][x]);
			}
		}
	}
}

void rotate(Move& move, const std::vector<std::vector<char>>& board)
{
	if (!move.has_move) return;

	const int board_size = board.size();
	move.x = board_size - 1 - move.x;
	std::swap(move.x, move.y);
}

void flip(std::vector<std::vector<char>>& board)
{
	const int board_size = board.size();
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size / 2; x++)
		{
			std::swap(board[y][x], board[y][board_size - 1 - x]);
		}
	}
}

void flip(Move& move, const std::vector<std::vector<char>>& board)
{
	if (!move.has_move) return;

	const int board_size = board.size();
	move.x = board_size - 1 - move.x;
}

struct MoveHash
{
	std::string key;
	bool is_flipped;
	int rotations_performed;
};

MoveHash hash(std::vector<std::vector<char>>& board)
{
	std::string key = toString(board);
	bool is_flipped_best = false;
	int rotations_performed_best = 0;
	for (int i = 0; i < 4; i++)
	{
		rotate(board);

		auto current_string = toString(board);
		if (current_string < key)
		{
			key = current_string;
			is_flipped_best = false;
			rotations_performed_best = i;
		}
	}

	flip(board);
	for (int i = 0; i < 4; i++)
	{
		rotate(board);

		auto current_string = toString(board);
		if (current_string < key)
		{
			key = current_string;
			is_flipped_best = true;
			rotations_performed_best = i;
		}
	}

	return { key, is_flipped_best, rotations_performed_best };
}

Move MoveMap::getMove(std::vector<std::vector<char>> board)
{
	const auto move_hash = hash(board);
	Move move = map[move_hash.key];

	for (int i = move_hash.rotations_performed; i < 4; i++)
		rotate(move, board);
	if (move_hash.is_flipped)
		flip(move, board);

	return move;
}

void MoveMap::setMove(std::vector<std::vector<char>> board, Move move)
{
	const auto move_hash = hash(board);

	if (move_hash.is_flipped)
		flip(move, board);
	for (int i = 0; i < move_hash.rotations_performed; i++)
		rotate(move, board);

	map[move_hash.key] = move;
}
