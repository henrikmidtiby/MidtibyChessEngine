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
	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(3, 6), WHITE_PAWN);
	board.placePiece(Position(7, 3), BLACK_KING);


	int counter = 0;

	// Shortest possible mate 13, 11, 17, 14

	while(true)
	{
		board.printBoard();
		std::vector<Move> moves = board.legalMoves();
		board.printMovesFromList(moves);
		std::cout << "Enter move number: ";
		std::cin >> counter;
		if(counter <= (int) moves.size())
			board.performMove(moves.at(counter - 1));
	}
	return 0;
}

