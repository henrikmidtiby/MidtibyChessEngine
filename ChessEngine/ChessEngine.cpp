// ChessEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UnitTest++.h"
#include "tests.h"
#include "chessboard.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	// Only perform unit tests if one additional argument is given
	if(argc == 2)
	{
		return UnitTest::RunAllTests();
	}

	ChessBoard board;
	board.initializeGame();

	int counter = 0;

	while(true)
	{
		board.printBoard();
		std::vector<Move> moves = board.legalMoves();
		board.printMovesFromList(moves);
		std::cin >> counter;
		board.performMove(moves.at(counter - 1));
	}
	return 0;
}

