#include "Board.h"
#include <iostream>

int main()
{
	int board_size = 3;

	Board board(board_size);
	
	for (int i = 0; i < board_size * board_size; i++)
	{
		if (i % 2 == 1)
		{
			auto move = board.getBestMove({ 'X', 'O' }, 1);
			board.place(move.y, move.x, 'O');
		}
		else
		{
			int y, x;
			std::cin >> x >> y;
			board.place(y, x, 'X');
		}
		board.print();
	}

	return 0;
}