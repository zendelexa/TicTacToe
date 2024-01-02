#pragma once

#include "Move.h"
#include <map>
#include <string>
#include <vector>

class MoveMap
{
	std::map<std::string, Move> map;

public:
	Move getMove(std::vector<std::vector<char>> board);
	void setMove(std::vector<std::vector<char>> board, Move move);
};