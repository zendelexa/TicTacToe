#pragma once
#include <vector>

struct Move
{
	bool has_move = false;
	uint8_t y;
	uint8_t x;
	uint8_t moves_remaining = 0;
	std::vector<int> evaluation;

	Move(const uint8_t players_amount, const int v);
	Move(const uint8_t y, const uint8_t x, const std::vector<int>& results);

	bool isWorse(const Move& other, uint8_t current_player) const;

	bool isSame(const Move& other, uint8_t current_player) const;
};