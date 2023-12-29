#pragma once
#include <vector>

struct Move
{
	bool has_move = false;
	int y;
	int x;
	int moves_remaining = 1e9;
	std::vector<int> evaluation;

	Move();
	Move(const int players_amount, const int start_evaluation_value);
	Move(const int y, const int x, const std::vector<int>& results);

	bool isWorse(const Move& other, int current_player) const;

	bool isSame(const Move& other, int current_player) const;
};