#include "Move.h"

Move::Move(const uint8_t players_amount, const int v) : evaluation(std::vector<int>(players_amount, v)) {}
Move::Move(const uint8_t y, const uint8_t x, const std::vector<int>& results) : has_move(true), y(y), x(x), evaluation(results) {}

bool Move::isWorse(const Move& other, uint8_t current_player) const
{
	if (other.evaluation[current_player] > evaluation[current_player])
	{
		return true;
	}
	return other.evaluation[current_player] > evaluation[current_player];
}

bool Move::isSame(const Move& other, uint8_t current_player) const
{
	return other.evaluation[current_player] == evaluation[current_player] && moves_remaining == other.moves_remaining;
}