#include "Board.h"
#include <iostream>

const char BLANK_TILE = ' ';
const char TIE_SYMBOL = '-';

int main()
{
	std::cout << "Board size: ";
	int board_size;
	std::cin >> board_size;

	std::cout << "Players amount: ";
	int players_amount;
	std::cin >> players_amount;

	Board board(board_size, players_amount);
	
	for (int i = 0; i < board_size * board_size; i++)
	{
		if (i % players_amount == 0)
		{
			system("cls");
			board.print();
			int y, x;
			std::cout << "x y: ";
			std::cin >> x >> y;
			x--; y--;
			board.place(y, x, 0);
		}
		else
		{
			auto move = board.getBestMove(i % players_amount);
			board.place(move.y, move.x, i % players_amount);
		}

		auto winner = board.checkWin();
		if (winner != BLANK_TILE)
		{
			system("cls");
			board.print();
			if (winner == TIE_SYMBOL) std::cout << "Tie";
			else std::cout << winner << " won!";
			break;
		}
	}

	return 0;
}