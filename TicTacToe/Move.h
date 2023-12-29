#pragma once
#include <vector>

struct Move
{
	bool has_move = false;
	int y;
	int x;
	int moves_remaining = 0;
	std::vector<int> evaluation;

	Move(const int players_amount, const int v);
	Move(const int y, const int x, const std::vector<int>& results);

	bool isWorse(const Move& other, int current_player) const;

	bool isSame(const Move& other, int current_player) const;
};