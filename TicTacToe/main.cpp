#include "Board.h"
#include <iostream>

int main()
{
	Board board(2);
	board.place(0, 0, 'X');
	board.place(1, 0, 'X');
	board.print();
	std::cout << board.checkWin();

	return 0;
}