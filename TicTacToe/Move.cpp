#include "Move.h"

Move::Move(const int players_amount, const int v) : evaluation(std::vector<int>(players_amount, v)) {}
Move::Move(const int y, const int x, const std::vector<int>& results) : has_move(true), y(y), x(x), evaluation(results) {}

bool Move::isWorse(const Move& other, int current_player) const
{
	if (other.evaluation[current_player] > evaluation[current_player])
	{
		return true;
	}
	return other.evaluation[current_player] > evaluation[current_player];
}

bool Move::isSame(const Move& other, int current_player) const
{
	return other.evaluation[current_player] == evaluation[current_player] && moves_remaining == other.moves_remaining;
}