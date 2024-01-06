#pragma once

struct Move
{
	bool has_move = false;
	int y = -1;
	int x = -1;
	char evaluation;

	Move();
	Move(char evaluation);
	Move(int y, int x, char evaluation);

	bool isWorse(const Move& other, char current_player) const;

	bool isSame(const Move& other, char current_player) const;
};