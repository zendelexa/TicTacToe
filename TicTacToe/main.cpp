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
	std::vector<char> players(players_amount);
	for (int i = 0; i < players_amount; i++)
		players[i] = 'A' + (char)i;

	Board board(board_size);
	
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
			board.place(y, x, players[0]);
		}
		else
		{
			auto move = board.getBestMove(players, 1);
			board.place(move.y, move.x, players[i % players_amount]);
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