#include "chessboard.h"
TEST( HelloUnitTestPP )
{
	CHECK( true );
}

TEST( InitializeEmptyChessBoard )
{
	ChessBoard board;
}

TEST( SetupChessBoardInInitialPosition )
{
	ChessBoard board;
	board.initializeGame();

	CHECK(board.sideToMove() == WHITE);

	CHECK(board.get(0, 0) == WHITE_ROOK);
	CHECK(board.get(1, 0) == WHITE_KNIGHT);
	CHECK(board.get(2, 0) == WHITE_BISHOP);
	CHECK(board.get(3, 0) == WHITE_QUEEN);
	CHECK(board.get(4, 0) == WHITE_KING);
	CHECK(board.get(5, 0) == WHITE_BISHOP);
	CHECK(board.get(6, 0) == WHITE_KNIGHT);
	CHECK(board.get(7, 0) == WHITE_ROOK);

	CHECK(board.get(0, 1) == WHITE_PAWN);
	CHECK(board.get(1, 1) == WHITE_PAWN);
	CHECK(board.get(2, 1) == WHITE_PAWN);
	CHECK(board.get(3, 1) == WHITE_PAWN);
	CHECK(board.get(4, 1) == WHITE_PAWN);
	CHECK(board.get(5, 1) == WHITE_PAWN);
	CHECK(board.get(6, 1) == WHITE_PAWN);
	CHECK(board.get(7, 1) == WHITE_PAWN);

	for(int i = 0; i < 8; i++)
	{
		for(int j = 2; j < 6; j++)
		{
			CHECK(board.get(i, j) == NO_PIECE);
		}
	}

	CHECK(board.get(0, 6) == BLACK_PAWN);
	CHECK(board.get(1, 6) == BLACK_PAWN);
	CHECK(board.get(2, 6) == BLACK_PAWN);
	CHECK(board.get(3, 6) == BLACK_PAWN);
	CHECK(board.get(4, 6) == BLACK_PAWN);
	CHECK(board.get(5, 6) == BLACK_PAWN);
	CHECK(board.get(6, 6) == BLACK_PAWN);
	CHECK(board.get(7, 6) == BLACK_PAWN);

	CHECK(board.get(0, 7) == BLACK_ROOK);
	CHECK(board.get(1, 7) == BLACK_KNIGHT);
	CHECK(board.get(2, 7) == BLACK_BISHOP);
	CHECK(board.get(3, 7) == BLACK_QUEEN);
	CHECK(board.get(4, 7) == BLACK_KING);
	CHECK(board.get(5, 7) == BLACK_BISHOP);
	CHECK(board.get(6, 7) == BLACK_KNIGHT);
	CHECK(board.get(7, 7) == BLACK_ROOK);
}

TEST ( PerformOneMoveFromTheInitialPosition )
{
	ChessBoard board;
	board.initializeGame();
	board.performMove(3, 1, 3, 3);
	CHECK(board.get(3, 1) == NO_PIECE);
	CHECK(board.get(3, 3) == WHITE_PAWN);
	CHECK(board.sideToMove() == BLACK);
}

