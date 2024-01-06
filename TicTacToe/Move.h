#pragma once

struct Move
{
	bool has_move = false;
	int y = -1;
	int x = -1;
	int moves_remaining = 1e9;
	char evaluation;

	Move();
	Move(char evaluation);
	Move(int y, int x, int moves_remaining, char evaluation);

	bool isWorse(const Move& other, char current_player) const;

	bool isSame(const Move& other, char current_player) const;
};