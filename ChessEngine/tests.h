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

	board.performMove(3, 6, 3, 4);
	CHECK(board.get(3, 6) == NO_PIECE);
	CHECK(board.get(3, 4) == BLACK_PAWN);
	CHECK(board.sideToMove() == WHITE);
}

TEST ( IsKingUnderAttackInInitialPosition )
{
	ChessBoard board;
	board.initializeGame();
	CHECK(!board.isWhiteKingUnderAttack());
	CHECK(!board.isBlackKingUnderAttack());
}

TEST ( ClearBoard )
{
	ChessBoard board;
	board.clearBoard();

	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			CHECK(board.get(i, j) == NO_PIECE);

	CHECK(board.sideToMove() == WHITE);
}

TEST ( PlacePiece )
{
	ChessBoard board;
	board.clearBoard();
	board.placePiece(3, 3, WHITE_KING);
	CHECK(board.get(3, 3) == WHITE_KING);
}

TEST ( SetSideToMove )
{
	ChessBoard board;
	board.setSideToMove(WHITE);
	CHECK(board.sideToMove() == WHITE);
	board.setSideToMove(BLACK);
	CHECK(board.sideToMove() == BLACK);
}

TEST ( IsKingAttackedByRook )
{
	ChessBoard board;
	board.clearBoard();

	// Place a rook above the king
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(3, 6, BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());
	
	// Put a piece in between
	board.placePiece(3, 5, BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook below the king
	board.clearBoard();
	board.placePiece(3, 6, WHITE_KING);
	board.placePiece(3, 3, BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());

	// Put a piece in between
	board.placePiece(3, 5, BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook to the right of the king
	board.clearBoard();
	board.placePiece(1, 3, WHITE_KING);
	board.placePiece(3, 3, BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());

	// Place a rook to the left of the king
	board.clearBoard();
	board.placePiece(6, 3, WHITE_KING);
	board.placePiece(3, 3, BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());
}

TEST ( FirstEncounteredPieceFromCurrentPosition )
{
	ChessBoard board;
	board.clearBoard();
	board.placePiece(3, 6, BLACK_ROOK);
	CHECK(board.firstPieceInDirection(3, 3, 1, 0) == NO_PIECE);
	CHECK(board.firstPieceInDirection(3, 3, 0, 1) == BLACK_ROOK);

	board.clearBoard();
	board.placePiece(7, 7, BLACK_QUEEN);
	CHECK(board.firstPieceInDirection(0, 0, 1, 1) == BLACK_QUEEN);
	CHECK(board.firstPieceInDirection(3, 3, 0, 1) == NO_PIECE);
}

TEST ( LocateKing )
{
	ChessBoard board;
	board.initializeGame();

	CHECK(board.locateWhiteKing() == std::make_pair(4, 0));
	CHECK(board.locateBlackKing() == std::make_pair(4, 7));
}

TEST ( IsKingAttackedByBishop )
{
	ChessBoard board;
	board.clearBoard();

	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(3, 6, BLACK_BISHOP);
	CHECK(!board.isWhiteKingUnderAttack());
	board.placePiece(6, 6, BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(6, 0, BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(0, 0, BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(0, 6, BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());
}

TEST ( IsKingAttackedByQueen )
{
	ChessBoard board;
	board.clearBoard();

	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(6, 6, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(6, 0, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(0, 0, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(0, 6, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());


	board.clearBoard();

	// Place a rook above the king
	board.placePiece(3, 3, WHITE_KING);
	board.placePiece(3, 6, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	// Put a piece in between
	board.placePiece(3, 5, BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook below the king
	board.clearBoard();
	board.placePiece(3, 6, WHITE_KING);
	board.placePiece(3, 3, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	// Put a piece in between
	board.placePiece(3, 5, BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook to the right of the king
	board.clearBoard();
	board.placePiece(1, 3, WHITE_KING);
	board.placePiece(3, 3, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	// Place a rook to the left of the king
	board.clearBoard();
	board.placePiece(6, 3, WHITE_KING);
	board.placePiece(3, 3, BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());
}