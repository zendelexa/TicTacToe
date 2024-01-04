#include "Move.h"
#include <vector>

const char BLANK_TILE = ' ';
const char TIE_SYMBOL = '-';

Move::Move() = default;

Move::Move(const char evaluation) : evaluation(evaluation) {}

Move::Move(const int y, const int x, const int moves_remaining, const char evaluation) : has_move(true), y(y), x(x), moves_remaining(moves_remaining), evaluation(evaluation) {}

bool isWorseHelper(char a, char b, char current_player)
{
	std::vector<char> order = { current_player, BLANK_TILE, TIE_SYMBOL };
	int rank_a = order.size();
	int rank_b = order.size();
	for (int i = 0; i < order.size(); i++)
	{
		if (a == order[i])
			rank_a = i;
		if (b == order[i])
			rank_b = i;
	}
	return rank_a > rank_b;
}

bool isSameHelper(char a, char b, char current_player)
{
	std::vector<char> order = { current_player, BLANK_TILE, TIE_SYMBOL };
	int rank_a = order.size();
	int rank_b = order.size();
	for (int i = 0; i < order.size(); i++)
	{
		if (a == order[i])
			rank_a = i;
		if (b == order[i])
			rank_b = i;
	}
	return rank_a == rank_b;
}

bool Move::isWorse(const Move& other, char current_player) const
{
	return isWorseHelper(evaluation, other.evaluation, current_player);
}

bool Move::isSame(const Move& other, char current_player) const
{
	return isSameHelper(evaluation, other.evaluation, current_player);
}
