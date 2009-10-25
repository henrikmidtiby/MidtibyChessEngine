#include "chessboard.h"

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
	board.performMove(Position(3, 1), Position(3, 3));
	CHECK(board.get(3, 1) == NO_PIECE);
	CHECK(board.get(3, 3) == WHITE_PAWN);
	CHECK(board.sideToMove() == BLACK);

	board.performMove(Position(3, 6), Position(3, 4));
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
	board.placePiece(Position(3, 3), WHITE_KING);
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

TEST ( IsWhiteKingAttackedByRook )
{
	ChessBoard board;
	board.clearBoard();

	// Place a rook above the king
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(3, 6), BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());
	
	// Put a piece in between
	board.placePiece(Position(3, 5), BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook below the king
	board.clearBoard();
	board.placePiece(Position(3, 6), WHITE_KING);
	board.placePiece(Position(3, 3), BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());

	// Put a piece in between
	board.placePiece(Position(3, 5), BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook to the right of the king
	board.clearBoard();
	board.placePiece(Position(1, 3), WHITE_KING);
	board.placePiece(Position(3, 3), BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());

	// Place a rook to the left of the king
	board.clearBoard();
	board.placePiece(Position(6, 3), WHITE_KING);
	board.placePiece(Position(3, 3), BLACK_ROOK);
	CHECK(board.isWhiteKingUnderAttack());
}

TEST ( IsBlackKingAttackedByRook )
{
	ChessBoard board;
	board.clearBoard();

	// Place a rook above the king
	board.placePiece(Position(3, 3), BLACK_KING);
	board.placePiece(Position(3, 6), WHITE_ROOK);
	CHECK(board.isBlackKingUnderAttack());

	// Put a piece in between
	board.placePiece(Position(3, 5), BLACK_PAWN);
	CHECK(!board.isBlackKingUnderAttack());

	// Place a rook below the king
	board.clearBoard();
	board.placePiece(Position(3, 6), BLACK_KING);
	board.placePiece(Position(3, 3), WHITE_ROOK);
	CHECK(board.isBlackKingUnderAttack());

	// Put a piece in between
	board.placePiece(Position(3, 5), BLACK_PAWN);
	CHECK(!board.isBlackKingUnderAttack());

	// Place a rook to the right of the king
	board.clearBoard();
	board.placePiece(Position(1, 3), BLACK_KING);
	board.placePiece(Position(3, 3), WHITE_ROOK);
	CHECK(board.isBlackKingUnderAttack());

	// Place a rook to the left of the king
	board.clearBoard();
	board.placePiece(Position(6, 3), BLACK_KING);
	board.placePiece(Position(3, 3), WHITE_ROOK);
	CHECK(board.isBlackKingUnderAttack());
}


TEST ( FirstEncounteredPieceFromCurrentPosition )
{
	ChessBoard board;
	board.clearBoard();
	board.placePiece(Position(3, 6), BLACK_ROOK);
	CHECK(board.firstPieceInDirection(Position(3, 3), 1, 0) == NO_PIECE);
	CHECK(board.firstPieceInDirection(Position(3, 3), 0, 1) == BLACK_ROOK);

	board.clearBoard();
	board.placePiece(Position(7, 7), BLACK_QUEEN);
	CHECK(board.firstPieceInDirection(Position(0, 0), 1, 1) == BLACK_QUEEN);
	CHECK(board.firstPieceInDirection(Position(3, 3), 0, 1) == NO_PIECE);
}

TEST ( LocateKing )
{
	ChessBoard board;
	board.initializeGame();

	CHECK(board.locateWhiteKing().isEqualTo(Position(4, 0)));
	CHECK(board.locateBlackKing().isEqualTo(Position(4, 7)));
}

TEST ( IsKingAttackedByBishop )
{
	ChessBoard board;
	board.clearBoard();

	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(3, 6), BLACK_BISHOP);
	CHECK(!board.isWhiteKingUnderAttack());
	board.placePiece(Position(6, 6), BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(6, 0), BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(0, 0), BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(0, 6), BLACK_BISHOP);
	CHECK(board.isWhiteKingUnderAttack());
}

TEST ( IsKingAttackedByQueen )
{
	ChessBoard board;
	board.clearBoard();

	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(6, 6), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(6, 0), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(0, 0), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(0, 6), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());


	board.clearBoard();

	// Place a rook above the king
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(3, 6), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	// Put a piece in between
	board.placePiece(Position(3, 5), BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook below the king
	board.clearBoard();
	board.placePiece(Position(3, 6), WHITE_KING);
	board.placePiece(Position(3, 3), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	// Put a piece in between
	board.placePiece(Position(3, 5), BLACK_PAWN);
	CHECK(!board.isWhiteKingUnderAttack());

	// Place a rook to the right of the king
	board.clearBoard();
	board.placePiece(Position(1, 3), WHITE_KING);
	board.placePiece(Position(3, 3), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());

	// Place a rook to the left of the king
	board.clearBoard();
	board.placePiece(Position(6, 3), WHITE_KING);
	board.placePiece(Position(3, 3), BLACK_QUEEN);
	CHECK(board.isWhiteKingUnderAttack());
}

TEST ( IsKingAttackedByKnight )
{
	ChessBoard board;
	board.clearBoard();

	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(6, 6), BLACK_KNIGHT);
	CHECK(!board.isWhiteKingUnderAttack());
	board.placePiece(Position(4, 5), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(2, 5), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(1, 4), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(1, 2), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(2, 1), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(4, 1), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(5, 2), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(5, 4), BLACK_KNIGHT);
	CHECK(board.isWhiteKingUnderAttack());

}

TEST ( GetPieceFromOutsideTheBoard )
{
	ChessBoard board;
	board.initializeGame();

	CHECK(board.get(0, 0) == WHITE_ROOK);
	CHECK(board.get(-1, 0) == OUTSIDE_BOARD);
	CHECK(board.get(8, 0) == OUTSIDE_BOARD);
	CHECK(board.get(0, -1) == OUTSIDE_BOARD);
	CHECK(board.get(0, 8) == OUTSIDE_BOARD);
}

TEST ( IsKingAttackedByPawn )
{
	ChessBoard board;

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(4, 4), BLACK_PAWN);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(2, 4), BLACK_PAWN);
	CHECK(board.isWhiteKingUnderAttack());
}

TEST ( IsKingAttackedByKing )
{
	ChessBoard board;

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(3, 4), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(2, 4), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(2, 3), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(2, 2), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(3, 2), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(4, 2), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(4, 3), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());

	board.clearBoard();
	board.placePiece(Position(3, 3), WHITE_KING);
	board.placePiece(Position(4, 4), BLACK_KING);
	CHECK(board.isWhiteKingUnderAttack());
}

TEST ( IsBlackPiece )
{
	ChessBoard board;
	CHECK(!board.isBlackPiece(WHITE_PAWN));
	CHECK(board.isBlackPiece(BLACK_PAWN));
	CHECK(board.isBlackPiece(BLACK_ROOK));
	CHECK(board.isBlackPiece(BLACK_KNIGHT));
	CHECK(board.isBlackPiece(BLACK_BISHOP));
	CHECK(board.isBlackPiece(BLACK_QUEEN));
	CHECK(board.isBlackPiece(BLACK_KING));
}

TEST ( IsWhitePiece )
{
	ChessBoard board;
	CHECK(board.isWhitePiece(WHITE_PAWN));
	CHECK(board.isWhitePiece(WHITE_ROOK));
	CHECK(board.isWhitePiece(WHITE_KNIGHT));
	CHECK(board.isWhitePiece(WHITE_BISHOP));
	CHECK(board.isWhitePiece(WHITE_QUEEN));
	CHECK(board.isWhitePiece(WHITE_KING));
}

TEST ( WhitePawnMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	// Single step forward
	board.clearBoard();
	board.placePiece(Position(3, 2), WHITE_PAWN);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 1);

	// Double step forward
	board.clearBoard();
	board.placePiece(Position(3, 1), WHITE_PAWN);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	// Strike left 
	board.clearBoard();
	board.placePiece(Position(3, 2), WHITE_PAWN);
	board.placePiece(Position(2, 3), BLACK_KING);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	// Strike right 
	board.clearBoard();
	board.placePiece(Position(3, 2), WHITE_PAWN);
	board.placePiece(Position(4, 3), BLACK_KING);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

}

TEST ( IsWhiteOrEmpty )
{
	ChessBoard board;
	CHECK(board.isWhiteOrEmpty(WHITE_PAWN));
	CHECK(board.isWhiteOrEmpty(NO_PIECE));
	CHECK(!board.isWhiteOrEmpty(BLACK_PAWN));
}

TEST ( IsBlackOrEmpty )
{
	ChessBoard board;
	CHECK(board.isBlackOrEmpty(BLACK_PAWN));
	CHECK(board.isBlackOrEmpty(NO_PIECE));
	CHECK(!board.isBlackOrEmpty(WHITE_PAWN));
}

TEST ( WhiteRookMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.placePiece(Position(0, 0), WHITE_ROOK);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 14);

	board.placePiece(Position(1, 0), BLACK_BISHOP);
	board.placePiece(Position(0, 1), BLACK_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	board.clearBoard();
	board.placePiece(Position(0, 0), WHITE_ROOK);
	board.placePiece(Position(0, 1), WHITE_ROOK);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 20);
}

TEST ( IsOutsideBoard )
{
	ChessBoard board;
	CHECK(board.isOutsideBoard(Position(-1, 0)));
}

TEST ( WhiteBishopMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.placePiece(Position(0, 0), WHITE_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);

	board.placePiece(Position(2, 2), BLACK_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	board.clearBoard();
	board.placePiece(Position(0, 7), WHITE_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);

	board.clearBoard();
	board.placePiece(Position(7, 0), WHITE_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);

	board.clearBoard();
	board.placePiece(Position(7, 7), WHITE_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);
}

TEST ( WhiteQueenMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.placePiece(Position(0, 0), WHITE_QUEEN);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 21);
}

TEST ( WhiteKingMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.placePiece(Position(0, 0), WHITE_KING);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 3);
}

TEST ( WhiteKnightMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.placePiece(Position(1, 0), WHITE_KNIGHT);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 3);	
}

TEST ( WhiteMovesFromOpeningPosition )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.initializeGame();
	moves = board.PossibleMoves();
	CHECK(moves.size() == 20);	
}


TEST ( BlackKnightMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(1, 0), BLACK_KNIGHT);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 3);	
}

TEST ( BlackPawnMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	// Single step forward
	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(3, 5), BLACK_PAWN);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 1);

	// Double step forward
	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(3, 6), BLACK_PAWN);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	// Strike left 
	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(3, 3), BLACK_PAWN);
	board.placePiece(Position(2, 2), WHITE_KING);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	// Strike right 
	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(3, 3), BLACK_PAWN);
	board.placePiece(Position(4, 2), WHITE_KING);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);
}

TEST ( BlackKingMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(0, 0), BLACK_KING);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 3);
}

TEST ( BlackBishopMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(0, 0), BLACK_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);

	board.placePiece(Position(2, 2), WHITE_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(0, 7), BLACK_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(7, 0), BLACK_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(7, 7), BLACK_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 7);
}

TEST ( BlackRookMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(0, 0), BLACK_ROOK);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 14);

	board.placePiece(Position(1, 0), WHITE_BISHOP);
	board.placePiece(Position(0, 1), WHITE_BISHOP);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 2);

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(0, 0), BLACK_ROOK);
	board.placePiece(Position(0, 1), BLACK_ROOK);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 20);
}
TEST ( BlackQueenMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(0, 0), BLACK_QUEEN);
	moves = board.PossibleMoves();
	CHECK(moves.size() == 21);
}

TEST ( LegalWhiteMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.placePiece(Position(0, 0), WHITE_KING);
	board.placePiece(Position(5, 0), BLACK_KING);
	board.placePiece(Position(1, 0), BLACK_QUEEN);
	moves = board.legalMoves();
	CHECK(moves.size() == 1);
}

TEST ( LegalBlackMoves )
{
	ChessBoard board;
	std::vector<Move> moves;

	board.clearBoard();
	board.setSideToMove(BLACK);
	board.placePiece(Position(0, 0), BLACK_KING);
	board.placePiece(Position(5, 0), WHITE_KING);
	board.placePiece(Position(1, 0), WHITE_QUEEN);
	moves = board.legalMoves();
	CHECK(moves.size() == 1);
}