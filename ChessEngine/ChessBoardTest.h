#include "chessboard.h"

class ChessBoardTest: public Test::Suite
{
	public:
		ChessBoardTest() { 
			//TEST_ADD(ChessBoardTest::test) 
			TEST_ADD(ChessBoardTest::InitializeEmptyChessBoard) 
				TEST_ADD(ChessBoardTest::SetupChessBoardInInitialPosition) 
				TEST_ADD(ChessBoardTest::PerformOneMoveFromTheInitialPosition) 
				TEST_ADD(ChessBoardTest::IsKingUnderAttackInInitialPosition) 
				TEST_ADD(ChessBoardTest::ClearBoard) 
				TEST_ADD(ChessBoardTest::PlacePiece) 
				TEST_ADD(ChessBoardTest::SetSideToMove) 
				TEST_ADD(ChessBoardTest::IsWhiteKingAttackedByRook) 
				TEST_ADD(ChessBoardTest::IsBlackKingAttackedByRook) 
				TEST_ADD(ChessBoardTest::FirstEncounteredPieceFromCurrentPosition) 
				TEST_ADD(ChessBoardTest::LocateKing) 
				TEST_ADD(ChessBoardTest::IsKingAttackedByBishop) 
				TEST_ADD(ChessBoardTest::IsKingAttackedByQueen) 
				TEST_ADD(ChessBoardTest::IsKingAttackedByKnight) 
				TEST_ADD(ChessBoardTest::GetPieceFromOutsideTheBoard) 
				TEST_ADD(ChessBoardTest::IsKingAttackedByPawn) 
				TEST_ADD(ChessBoardTest::IsKingAttackedByKing) 
				TEST_ADD(ChessBoardTest::IsBlackPiece) 
				TEST_ADD(ChessBoardTest::IsWhitePiece) 
				TEST_ADD(ChessBoardTest::WhitePawnMoves) 
				TEST_ADD(ChessBoardTest::IsWhiteOrEmpty) 
				TEST_ADD(ChessBoardTest::WhiteRookMoves) 
				TEST_ADD(ChessBoardTest::IsOutsideBoard) 
				TEST_ADD(ChessBoardTest::WhiteBishopMoves) 
				TEST_ADD(ChessBoardTest::WhiteQueenMoves) 
				TEST_ADD(ChessBoardTest::WhiteKingMoves) 
				TEST_ADD(ChessBoardTest::WhiteKnightMoves) 
				TEST_ADD(ChessBoardTest::WhiteMovesFromOpeningPosition) 
				TEST_ADD(ChessBoardTest::BlackKnightMoves) 
				TEST_ADD(ChessBoardTest::BlackPawnMoves) 
				TEST_ADD(ChessBoardTest::BlackKingMoves) 
				TEST_ADD(ChessBoardTest::BlackBishopMoves) 
				TEST_ADD(ChessBoardTest::BlackRookMoves) 
				TEST_ADD(ChessBoardTest::BlackQueenMoves) 
				TEST_ADD(ChessBoardTest::LegalWhiteMoves) 
				TEST_ADD(ChessBoardTest::LegalBlackMoves) 
				TEST_ADD(ChessBoardTest::LegalRookMoves) 
				TEST_ADD(ChessBoardTest::BlackIsCheckmate) 
				TEST_ADD(ChessBoardTest::WhiteIsCheckmate) 
				TEST_ADD(ChessBoardTest::PrintMoves) 
				TEST_ADD(ChessBoardTest::PromoteWhitePawn) 
				TEST_ADD(ChessBoardTest::PromoteBlackPawn) 
				TEST_ADD(ChessBoardTest::DetectMateUsingTheEvaluationFunction) 
				TEST_ADD(ChessBoardTest::PieceValues) 
				TEST_ADD(ChessBoardTest::MaterialBalanceAtInitialPosition) 
				TEST_ADD(ChessBoardTest::FindMateInZeroHalfMoves) 
				TEST_ADD(ChessBoardTest::FindMateInOneHalfMove) 
				TEST_ADD(ChessBoardTest::FindMateInThreeHalfMove) 
				TEST_ADD(ChessBoardTest::IllegalMoveLocator) 
				TEST_ADD(ChessBoardTest::BuildPositionFromFen) 
				TEST_ADD(ChessBoardTest::WhiteCasteling) 
				TEST_ADD(ChessBoardTest::TakeBackLastMove) 
		}
	private:
		void InitializeEmptyChessBoard()
		{
			ChessBoard board;
		}

		void SetupChessBoardInInitialPosition()
		{
			ChessBoard board;
			board.initializeGame();

			TEST_ASSERT(board.sideToMove() == WHITE);

			TEST_ASSERT(board.get(0, 0) == WHITE_ROOK);
			TEST_ASSERT(board.get(1, 0) == WHITE_KNIGHT);
			TEST_ASSERT(board.get(2, 0) == WHITE_BISHOP);
			TEST_ASSERT(board.get(3, 0) == WHITE_QUEEN);
			TEST_ASSERT(board.get(4, 0) == WHITE_KING);
			TEST_ASSERT(board.get(5, 0) == WHITE_BISHOP);
			TEST_ASSERT(board.get(6, 0) == WHITE_KNIGHT);
			TEST_ASSERT(board.get(7, 0) == WHITE_ROOK);

			TEST_ASSERT(board.get(0, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(1, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(2, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(3, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(4, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(5, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(6, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(7, 1) == WHITE_PAWN);

			for(int i = 0; i < 8; i++)
			{
				for(int j = 2; j < 6; j++)
				{
					TEST_ASSERT(board.get(i, j) == NO_PIECE);
				}
			}

			TEST_ASSERT(board.get(0, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(1, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(2, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(3, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(4, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(5, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(6, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(7, 6) == BLACK_PAWN);

			TEST_ASSERT(board.get(0, 7) == BLACK_ROOK);
			TEST_ASSERT(board.get(1, 7) == BLACK_KNIGHT);
			TEST_ASSERT(board.get(2, 7) == BLACK_BISHOP);
			TEST_ASSERT(board.get(3, 7) == BLACK_QUEEN);
			TEST_ASSERT(board.get(4, 7) == BLACK_KING);
			TEST_ASSERT(board.get(5, 7) == BLACK_BISHOP);
			TEST_ASSERT(board.get(6, 7) == BLACK_KNIGHT);
			TEST_ASSERT(board.get(7, 7) == BLACK_ROOK);
		}

		void PerformOneMoveFromTheInitialPosition ()
		{
			ChessBoard board;
			board.initializeGame();
			board.performMove(Position(3, 1), Position(3, 3));
			TEST_ASSERT(board.get(3, 1) == NO_PIECE);
			TEST_ASSERT(board.get(3, 3) == WHITE_PAWN);
			TEST_ASSERT(board.sideToMove() == BLACK);

			board.performMove(Position(3, 6), Position(3, 4));
			TEST_ASSERT(board.get(3, 6) == NO_PIECE);
			TEST_ASSERT(board.get(3, 4) == BLACK_PAWN);
			TEST_ASSERT(board.sideToMove() == WHITE);
		}

		void IsKingUnderAttackInInitialPosition ()
		{
			ChessBoard board;
			board.initializeGame();
			TEST_ASSERT(!board.isWhiteKingUnderAttack());
			TEST_ASSERT(!board.isBlackKingUnderAttack());
		}

		void ClearBoard ()
		{
			ChessBoard board;
			board.clearBoard();

			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 8; j++)
					TEST_ASSERT(board.get(i, j) == NO_PIECE);

			TEST_ASSERT(board.sideToMove() == WHITE);
		}

		void PlacePiece ()
		{
			ChessBoard board;
			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			TEST_ASSERT(board.get(3, 3) == WHITE_KING);
		}

		void SetSideToMove ()
		{
			ChessBoard board;
			board.setSideToMove(WHITE);
			TEST_ASSERT(board.sideToMove() == WHITE);
			board.setSideToMove(BLACK);
			TEST_ASSERT(board.sideToMove() == BLACK);
		}

		void IsWhiteKingAttackedByRook ()
		{
			ChessBoard board;
			board.clearBoard();

			// Place a rook above the king
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(3, 6), BLACK_ROOK);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			// Put a piece in between
			board.placePiece(Position(3, 5), BLACK_PAWN);
			TEST_ASSERT(!board.isWhiteKingUnderAttack());

			// Place a rook below the king
			board.clearBoard();
			board.placePiece(Position(3, 6), WHITE_KING);
			board.placePiece(Position(3, 3), BLACK_ROOK);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			// Put a piece in between
			board.placePiece(Position(3, 5), BLACK_PAWN);
			TEST_ASSERT(!board.isWhiteKingUnderAttack());

			// Place a rook to the right of the king
			board.clearBoard();
			board.placePiece(Position(1, 3), WHITE_KING);
			board.placePiece(Position(3, 3), BLACK_ROOK);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			// Place a rook to the left of the king
			board.clearBoard();
			board.placePiece(Position(6, 3), WHITE_KING);
			board.placePiece(Position(3, 3), BLACK_ROOK);
			TEST_ASSERT(board.isWhiteKingUnderAttack());
		}

		void IsBlackKingAttackedByRook ()
		{
			ChessBoard board;
			board.clearBoard();

			// Place a rook above the king
			board.placePiece(Position(3, 3), BLACK_KING);
			board.placePiece(Position(3, 6), WHITE_ROOK);
			TEST_ASSERT(board.isBlackKingUnderAttack());

			// Put a piece in between
			board.placePiece(Position(3, 5), BLACK_PAWN);
			TEST_ASSERT(!board.isBlackKingUnderAttack());

			// Place a rook below the king
			board.clearBoard();
			board.placePiece(Position(3, 6), BLACK_KING);
			board.placePiece(Position(3, 3), WHITE_ROOK);
			TEST_ASSERT(board.isBlackKingUnderAttack());

			// Put a piece in between
			board.placePiece(Position(3, 5), BLACK_PAWN);
			TEST_ASSERT(!board.isBlackKingUnderAttack());

			// Place a rook to the right of the king
			board.clearBoard();
			board.placePiece(Position(1, 3), BLACK_KING);
			board.placePiece(Position(3, 3), WHITE_ROOK);
			TEST_ASSERT(board.isBlackKingUnderAttack());

			// Place a rook to the left of the king
			board.clearBoard();
			board.placePiece(Position(6, 3), BLACK_KING);
			board.placePiece(Position(3, 3), WHITE_ROOK);
			TEST_ASSERT(board.isBlackKingUnderAttack());
		}


		void FirstEncounteredPieceFromCurrentPosition ()
		{
			ChessBoard board;
			board.clearBoard();
			board.placePiece(Position(3, 6), BLACK_ROOK);
			TEST_ASSERT(board.firstPieceInDirection(Position(3, 3), 1, 0) == NO_PIECE);
			TEST_ASSERT(board.firstPieceInDirection(Position(3, 3), 0, 1) == BLACK_ROOK);

			board.clearBoard();
			board.placePiece(Position(7, 7), BLACK_QUEEN);
			TEST_ASSERT(board.firstPieceInDirection(Position(0, 0), 1, 1) == BLACK_QUEEN);
			TEST_ASSERT(board.firstPieceInDirection(Position(3, 3), 0, 1) == NO_PIECE);
		}

		void LocateKing ()
		{
			ChessBoard board;
			board.initializeGame();

			TEST_ASSERT(board.locateWhiteKing().isEqualTo(Position(4, 0)));
			TEST_ASSERT(board.locateBlackKing().isEqualTo(Position(4, 7)));
		}

		void IsKingAttackedByBishop ()
		{
			ChessBoard board;
			board.clearBoard();

			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(3, 6), BLACK_BISHOP);
			TEST_ASSERT(!board.isWhiteKingUnderAttack());
			board.placePiece(Position(6, 6), BLACK_BISHOP);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(6, 0), BLACK_BISHOP);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(0, 0), BLACK_BISHOP);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(0, 6), BLACK_BISHOP);
			TEST_ASSERT(board.isWhiteKingUnderAttack());
		}

		void IsKingAttackedByQueen ()
		{
			ChessBoard board;
			board.clearBoard();

			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(6, 6), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(6, 0), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(0, 0), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(0, 6), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());


			board.clearBoard();

			// Place a rook above the king
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(3, 6), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			// Put a piece in between
			board.placePiece(Position(3, 5), BLACK_PAWN);
			TEST_ASSERT(!board.isWhiteKingUnderAttack());

			// Place a rook below the king
			board.clearBoard();
			board.placePiece(Position(3, 6), WHITE_KING);
			board.placePiece(Position(3, 3), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			// Put a piece in between
			board.placePiece(Position(3, 5), BLACK_PAWN);
			TEST_ASSERT(!board.isWhiteKingUnderAttack());

			// Place a rook to the right of the king
			board.clearBoard();
			board.placePiece(Position(1, 3), WHITE_KING);
			board.placePiece(Position(3, 3), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			// Place a rook to the left of the king
			board.clearBoard();
			board.placePiece(Position(6, 3), WHITE_KING);
			board.placePiece(Position(3, 3), BLACK_QUEEN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());
		}

		void IsKingAttackedByKnight ()
		{
			ChessBoard board;
			board.clearBoard();

			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(6, 6), BLACK_KNIGHT);
			TEST_ASSERT(!board.isWhiteKingUnderAttack());
			board.placePiece(Position(4, 5), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(2, 5), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(1, 4), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(1, 2), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(2, 1), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(4, 1), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(5, 2), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(5, 4), BLACK_KNIGHT);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

		}

		void GetPieceFromOutsideTheBoard ()
		{
			ChessBoard board;
			board.initializeGame();

			TEST_ASSERT(board.get(0, 0) == WHITE_ROOK);
			TEST_ASSERT(board.get(-1, 0) == OUTSIDE_BOARD);
			TEST_ASSERT(board.get(8, 0) == OUTSIDE_BOARD);
			TEST_ASSERT(board.get(0, -1) == OUTSIDE_BOARD);
			TEST_ASSERT(board.get(0, 8) == OUTSIDE_BOARD);
		}

		void IsKingAttackedByPawn ()
		{
			ChessBoard board;

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(4, 4), BLACK_PAWN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(2, 4), BLACK_PAWN);
			TEST_ASSERT(board.isWhiteKingUnderAttack());
		}

		void IsKingAttackedByKing ()
		{
			ChessBoard board;

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(3, 4), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(2, 4), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(2, 3), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(2, 2), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(3, 2), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(4, 2), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(4, 3), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());

			board.clearBoard();
			board.placePiece(Position(3, 3), WHITE_KING);
			board.placePiece(Position(4, 4), BLACK_KING);
			TEST_ASSERT(board.isWhiteKingUnderAttack());
		}

		void IsBlackPiece ()
		{
			ChessBoard board;
			TEST_ASSERT(!board.isBlackPiece(WHITE_PAWN));
			TEST_ASSERT(board.isBlackPiece(BLACK_PAWN));
			TEST_ASSERT(board.isBlackPiece(BLACK_ROOK));
			TEST_ASSERT(board.isBlackPiece(BLACK_KNIGHT));
			TEST_ASSERT(board.isBlackPiece(BLACK_BISHOP));
			TEST_ASSERT(board.isBlackPiece(BLACK_QUEEN));
			TEST_ASSERT(board.isBlackPiece(BLACK_KING));
		}

		void IsWhitePiece ()
		{
			ChessBoard board;
			TEST_ASSERT(board.isWhitePiece(WHITE_PAWN));
			TEST_ASSERT(board.isWhitePiece(WHITE_ROOK));
			TEST_ASSERT(board.isWhitePiece(WHITE_KNIGHT));
			TEST_ASSERT(board.isWhitePiece(WHITE_BISHOP));
			TEST_ASSERT(board.isWhitePiece(WHITE_QUEEN));
			TEST_ASSERT(board.isWhitePiece(WHITE_KING));
		}

		void WhitePawnMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			// Single step forward
			board.clearBoard();
			board.placePiece(Position(3, 2), WHITE_PAWN);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 1);

			// Double step forward
			board.clearBoard();
			board.placePiece(Position(3, 1), WHITE_PAWN);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			// Strike left 
			board.clearBoard();
			board.placePiece(Position(3, 2), WHITE_PAWN);
			board.placePiece(Position(2, 3), BLACK_KING);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			// Strike right 
			board.clearBoard();
			board.placePiece(Position(3, 2), WHITE_PAWN);
			board.placePiece(Position(4, 3), BLACK_KING);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

		}

		void IsWhiteOrEmpty ()
		{
			ChessBoard board;
			TEST_ASSERT(board.isWhiteOrEmpty(WHITE_PAWN));
			TEST_ASSERT(board.isWhiteOrEmpty(NO_PIECE));
			TEST_ASSERT(!board.isWhiteOrEmpty(BLACK_PAWN));
		}

		void IsBlackOrEmpty ()
		{
			ChessBoard board;
			TEST_ASSERT(board.isBlackOrEmpty(BLACK_PAWN));
			TEST_ASSERT(board.isBlackOrEmpty(NO_PIECE));
			TEST_ASSERT(!board.isBlackOrEmpty(WHITE_PAWN));
		}

		void WhiteRookMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_ROOK);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 14);

			board.placePiece(Position(1, 0), BLACK_BISHOP);
			board.placePiece(Position(0, 1), BLACK_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_ROOK);
			board.placePiece(Position(0, 1), WHITE_ROOK);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 20);
		}

		void IsOutsideBoard ()
		{
			ChessBoard board;
			TEST_ASSERT(board.isOutsideBoard(Position(-1, 0)));
		}

		void WhiteBishopMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);

			board.placePiece(Position(2, 2), BLACK_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			board.clearBoard();
			board.placePiece(Position(0, 7), WHITE_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);

			board.clearBoard();
			board.placePiece(Position(7, 0), WHITE_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);

			board.clearBoard();
			board.placePiece(Position(7, 7), WHITE_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);
		}

		void WhiteQueenMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_QUEEN);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 21);
		}

		void WhiteKingMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_KING);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 3);
		}

		void WhiteKnightMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.placePiece(Position(1, 0), WHITE_KNIGHT);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 3);	
		}

		void WhiteMovesFromOpeningPosition ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.initializeGame();
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 20);	
		}


		void BlackKnightMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(1, 0), BLACK_KNIGHT);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 3);	
		}

		void BlackPawnMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			// Single step forward
			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(3, 5), BLACK_PAWN);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 1);

			// Double step forward
			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(3, 6), BLACK_PAWN);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			// Strike left 
			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(3, 3), BLACK_PAWN);
			board.placePiece(Position(2, 2), WHITE_KING);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			// Strike right 
			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(3, 3), BLACK_PAWN);
			board.placePiece(Position(4, 2), WHITE_KING);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);
		}

		void BlackKingMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 0), BLACK_KING);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 3);
		}

		void BlackBishopMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 0), BLACK_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);

			board.placePiece(Position(2, 2), WHITE_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 7), BLACK_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(7, 0), BLACK_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(7, 7), BLACK_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 7);
		}

		void BlackRookMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 0), BLACK_ROOK);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 14);

			board.placePiece(Position(1, 0), WHITE_BISHOP);
			board.placePiece(Position(0, 1), WHITE_BISHOP);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 2);

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 0), BLACK_ROOK);
			board.placePiece(Position(0, 1), BLACK_ROOK);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 20);
		}

		void BlackQueenMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 0), BLACK_QUEEN);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 21);
		}

		void LegalWhiteMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_KING);
			board.placePiece(Position(5, 0), BLACK_KING);
			board.placePiece(Position(1, 0), BLACK_QUEEN);
			moves = board.legalMoves();
			TEST_ASSERT(moves.size() == 1);
		}

		void LegalBlackMoves ()
		{
			ChessBoard board;
			std::vector<Move> moves;

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 0), BLACK_KING);
			board.placePiece(Position(5, 0), WHITE_KING);
			board.placePiece(Position(1, 0), WHITE_QUEEN);
			moves = board.legalMoves();
			TEST_ASSERT(moves.size() == 1);
		}

		void LegalRookMoves ()
		{
			ChessBoard board;
			board.clearBoard();
			board.placePiece(Position(0, 7), WHITE_ROOK);
			TEST_ASSERT(!board.isLocationAttackedByWhitePieces(Position(1, 6)));

			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 7), BLACK_ROOK);
			TEST_ASSERT(!board.isLocationAttackedByBlackPieces(Position(1, 6)));
		}

		void BlackIsCheckmate()
		{
			ChessBoard board;

			board.clearBoard();
			board.setSideToMove(BLACK);

			board.placePiece(Position(3, 5), WHITE_KING);
			board.placePiece(Position(3, 7), BLACK_KING);
			TEST_ASSERT(!board.isBlackMate());

			board.placePiece(Position(0, 7), WHITE_ROOK);
			TEST_ASSERT(board.isBlackMate());


			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(3, 5), WHITE_KING);
			board.placePiece(Position(0, 7), WHITE_ROOK);
			board.placePiece(Position(2, 7), BLACK_KING);

			std::vector <Move> pMoves = board.possibleBlackMoves();

			std::vector <Move> moves = board.legalMoves();
			TEST_ASSERT(moves.size() == 1);
			TEST_ASSERT(!board.isBlackMate());
		}


		void WhiteIsCheckmate()
		{
			ChessBoard board;

			board.clearBoard();
			board.setSideToMove(WHITE);

			board.placePiece(Position(3, 5), BLACK_KING);
			board.placePiece(Position(3, 7), WHITE_KING);
			TEST_ASSERT(!board.isWhiteMate());

			board.placePiece(Position(0, 7), BLACK_ROOK);
			TEST_ASSERT(board.isWhiteMate());


			board.clearBoard();
			board.setSideToMove(WHITE);
			board.placePiece(Position(3, 5), BLACK_KING);
			board.placePiece(Position(0, 7), BLACK_ROOK);
			board.placePiece(Position(2, 7), WHITE_KING);

			std::vector <Move> pMoves = board.possibleBlackMoves();

			std::vector <Move> moves = board.legalMoves();
			TEST_ASSERT(moves.size() == 1);
			TEST_ASSERT(!board.isWhiteMate());
		}

		void PrintMoves ()
		{
			Move mov(0, 0, 0, 4);
			TEST_ASSERT(mov.toString() == "a1a5");

			mov = Move(1, 1, 5, 5);
			TEST_ASSERT(mov.toString() == "b2f6");

			mov = Move(3, 6, 3, 7, PROMOTE_TO_QUEEN);
			TEST_ASSERT(mov.toString() == "d7d8Q");

			mov = Move(3, 6, 3, 7, PROMOTE_TO_ROOK);
			TEST_ASSERT(mov.toString() == "d7d8R");

			mov = Move(3, 6, 3, 7, PROMOTE_TO_BISHOP);
			TEST_ASSERT(mov.toString() == "d7d8B");

			mov = Move(3, 6, 3, 7, PROMOTE_TO_KNIGHT);
			TEST_ASSERT(mov.toString() == "d7d8N");

			mov = Move(3, 6, 3, 7, CASTLE_KING);
			//	TEST_ASSERT(mov.toString() == "O-O");

			mov = Move(3, 6, 3, 7, CASTLE_QUEEN);
			//	TEST_ASSERT(mov.toString() == "O-O-O");

			// TODO
			// Special notation for promotion and castling
		}


		void PromoteWhitePawn ()
		{
			ChessBoard board;
			board.clearBoard();
			board.placePiece(Position(4, 6), WHITE_PAWN);
			std::vector<Move> moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 4);

			board.placePiece(Position(5, 7), BLACK_KNIGHT);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 8);

			ChessBoard board1(board);
			board1.performMove(Move(Position(4, 6), Position(5, 7), PROMOTE_TO_QUEEN));
			TEST_ASSERT(board1.get(5, 7) == WHITE_QUEEN);

			board1 = ChessBoard(board);
			board1.performMove(Move(Position(4, 6), Position(5, 7), PROMOTE_TO_ROOK));
			TEST_ASSERT(board1.get(5, 7) == WHITE_ROOK);

			board1 = ChessBoard(board);
			board1.performMove(Move(Position(4, 6), Position(5, 7), PROMOTE_TO_KNIGHT));
			TEST_ASSERT(board1.get(5, 7) == WHITE_KNIGHT);

			board1 = ChessBoard(board);
			board1.performMove(Move(Position(4, 6), Position(5, 7), PROMOTE_TO_BISHOP));
			TEST_ASSERT(board1.get(5, 7) == WHITE_BISHOP);
		}


		void PromoteBlackPawn ()
		{
			ChessBoard board;
			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(4, 1), BLACK_PAWN);
			std::vector<Move> moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 4);

			board.placePiece(Position(5, 0), WHITE_KNIGHT);
			moves = board.possibleMoves();
			TEST_ASSERT(moves.size() == 8);
		}

		void EvaluationDataType ()
		{
			TEST_ASSERT(Evaluation(0) == Evaluation(0));
			TEST_ASSERT(Evaluation(0) != Evaluation(0, 0, WHITE_WINS));
			TEST_ASSERT(Evaluation(0, 1, WHITE_WINS) != Evaluation(0, 0, WHITE_WINS));

			TEST_ASSERT(Evaluation(0, 1, WHITE_WINS) == Evaluation(0, 1, WHITE_WINS));
			TEST_ASSERT(Evaluation(0, 1, BLACK_WINS) != Evaluation(0, 1, WHITE_WINS));
			TEST_ASSERT(Evaluation(0.1) != Evaluation(0.0));

			TEST_ASSERT(Evaluation(0, 1, WHITE_WINS) > Evaluation(0, 1, BLACK_WINS));
			TEST_ASSERT(!(Evaluation(0, 1, BLACK_WINS) > Evaluation(0, 1, WHITE_WINS)));

			TEST_ASSERT(Evaluation(0, 1, WHITE_WINS) > Evaluation(0, 2, WHITE_WINS));
			TEST_ASSERT(!(Evaluation(0, 3, WHITE_WINS) > Evaluation(0, 2, WHITE_WINS)));

			TEST_ASSERT(Evaluation(0, 3, BLACK_WINS) > Evaluation(0, 2, BLACK_WINS));
			TEST_ASSERT(!(Evaluation(0, 1, BLACK_WINS) > Evaluation(0, 2, BLACK_WINS)));

			TEST_ASSERT(Evaluation(3) > Evaluation(2));
			TEST_ASSERT(!(Evaluation(1) > Evaluation(2)));
		}

		void DetectMateUsingTheEvaluationFunction ()
		{
			ChessBoard board;
			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 7), WHITE_ROOK);
			board.placePiece(Position(4, 5), WHITE_KING);
			board.placePiece(Position(4, 7), BLACK_KING);
			TEST_ASSERT(board.staticEvaluation() == Evaluation(0, 0, WHITE_WINS));
		}

		void PieceValues ()
		{
			ChessBoard board;
			TEST_ASSERT(board.pieceValue(WHITE_KING) == 0);
			TEST_ASSERT(board.pieceValue(BLACK_KING) == 0);
			TEST_ASSERT(board.pieceValue(WHITE_QUEEN) == 900);
			TEST_ASSERT(board.pieceValue(BLACK_QUEEN) == -900);
			TEST_ASSERT(board.pieceValue(WHITE_ROOK) == 500);
			TEST_ASSERT(board.pieceValue(BLACK_ROOK) == -500);
			TEST_ASSERT(board.pieceValue(WHITE_KNIGHT) == 300);
			TEST_ASSERT(board.pieceValue(BLACK_KNIGHT) == -300);
			TEST_ASSERT(board.pieceValue(WHITE_BISHOP) == 300);
			TEST_ASSERT(board.pieceValue(BLACK_BISHOP) == -300);
			TEST_ASSERT(board.pieceValue(WHITE_PAWN) == 100);
			TEST_ASSERT(board.pieceValue(BLACK_PAWN) == -100);
		}

		void MaterialBalanceAtInitialPosition ()
		{
			ChessBoard board;
			board.initializeGame();
			TEST_ASSERT(board.basicMaterialCount() == 0);
		}

		void FindMateInZeroHalfMoves ()
		{
			ChessBoard board;
			board.clearBoard();
			board.setSideToMove(BLACK);
			board.placePiece(Position(0, 7), WHITE_ROOK);
			board.placePiece(Position(4, 5), WHITE_KING);
			board.placePiece(Position(4, 7), BLACK_KING);
			int nodeCount = 0;
			std::vector<Move> pv;
			Evaluation eval = board.dynamicEvaluation(0, &nodeCount, pv);
			TEST_ASSERT(eval == Evaluation(0, 0, WHITE_WINS));
			eval = board.dynamicEvaluation(1, &nodeCount, pv);
			TEST_ASSERT(eval == Evaluation(0, 0, WHITE_WINS));
		}

		void FindMateInOneHalfMove ()
		{
			ChessBoard board;
			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_ROOK);
			board.placePiece(Position(4, 5), WHITE_KING);
			board.placePiece(Position(4, 7), BLACK_KING);
			int nodeCount = 0;
			std::vector<Move> pv;
			Evaluation eval = board.dynamicEvaluation(1, &nodeCount, pv);
			TEST_ASSERT(eval == Evaluation(0, 1, WHITE_WINS));
		}

		void FindMateInThreeHalfMove ()
		{
			ChessBoard board;
			board.clearBoard();
			board.placePiece(Position(0, 0), WHITE_ROOK);
			board.placePiece(Position(4, 5), WHITE_KING);
			board.placePiece(Position(3, 7), BLACK_KING);
			int nodeCount = 0;
			std::vector<Move> pv;
			Evaluation eval = board.dynamicEvaluation(3, &nodeCount, pv);
			TEST_ASSERT(eval == Evaluation(0, 3, WHITE_WINS));
		}

		void IllegalMoveLocator ()
		{
			ChessBoard board;
			board.initializeGame();
			board.performMove(Move(Position(7, 1), Position(7, 3)));
			board.performMove(Move(Position(3, 6), Position(3, 5)));
			std::vector<Move> moves = board.legalMoves();
			TEST_ASSERT(moves.size() == 21);
		}

		void BuildPositionFromFen ()
		{
			ChessBoard board;
			board.setupBoardFromFen((char*) "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			TEST_ASSERT(board.get(0, 0) == WHITE_ROOK);
			TEST_ASSERT(board.get(1, 0) == WHITE_KNIGHT);
			TEST_ASSERT(board.get(2, 0) == WHITE_BISHOP);
			TEST_ASSERT(board.get(3, 0) == WHITE_QUEEN);
			TEST_ASSERT(board.get(4, 0) == WHITE_KING);
			TEST_ASSERT(board.get(5, 0) == WHITE_BISHOP);
			TEST_ASSERT(board.get(6, 0) == WHITE_KNIGHT);
			TEST_ASSERT(board.get(7, 0) == WHITE_ROOK);

			TEST_ASSERT(board.get(0, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(1, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(2, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(3, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(4, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(5, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(6, 1) == WHITE_PAWN);
			TEST_ASSERT(board.get(7, 1) == WHITE_PAWN);

			for(int i = 0; i < 8; i++)
			{
				for(int j = 2; j < 6; j++)
				{
					TEST_ASSERT(board.get(i, j) == NO_PIECE);
				}
			}

			TEST_ASSERT(board.get(0, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(1, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(2, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(3, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(4, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(5, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(6, 6) == BLACK_PAWN);
			TEST_ASSERT(board.get(7, 6) == BLACK_PAWN);

			TEST_ASSERT(board.get(0, 7) == BLACK_ROOK);
			TEST_ASSERT(board.get(1, 7) == BLACK_KNIGHT);
			TEST_ASSERT(board.get(2, 7) == BLACK_BISHOP);
			TEST_ASSERT(board.get(3, 7) == BLACK_QUEEN);
			TEST_ASSERT(board.get(4, 7) == BLACK_KING);
			TEST_ASSERT(board.get(5, 7) == BLACK_BISHOP);
			TEST_ASSERT(board.get(6, 7) == BLACK_KNIGHT);
			TEST_ASSERT(board.get(7, 7) == BLACK_ROOK);

			TEST_ASSERT(board.sideToMove() == WHITE);

			TEST_ASSERT(board.whiteCastleKing == true);
			TEST_ASSERT(board.whiteCastleQueen == true);
			TEST_ASSERT(board.blackCastleKing == true);
			TEST_ASSERT(board.blackCastleQueen == true);

			board.setupBoardFromFen((char*) "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");

			TEST_ASSERT(board.whiteCastleKing == false);
			TEST_ASSERT(board.whiteCastleQueen == false);
			TEST_ASSERT(board.blackCastleKing == false);
			TEST_ASSERT(board.blackCastleQueen == false);

		}

		void WhiteCasteling ()
		{
			ChessBoard board;
			board.initializeGame();
			board.performMove(Move(Position(4, 1), Position(4, 3)));
			board.performMove(Move(Position(4, 6), Position(4, 4)));
			board.performMove(Move(Position(5, 0), Position(2, 3)));
			board.performMove(Move(Position(5, 7), Position(2, 4)));
			board.performMove(Move(Position(6, 0), Position(5, 2)));
			board.performMove(Move(Position(6, 7), Position(5, 5)));

			std::vector<Move> moves;
			moves = board.possibleMoves();

			TEST_ASSERT(moves.size() == 33);

			board.performMove(Move(Position(4, 0), Position(6, 0)));
			TEST_ASSERT(board.get(6, 0) == WHITE_KING);
			TEST_ASSERT(board.get(5, 0) == WHITE_ROOK);
			TEST_ASSERT(board.get(4, 0) == NO_PIECE);
			TEST_ASSERT(board.get(7, 0) == NO_PIECE);

		}

		void TakeBackLastMove ()
		{
			ChessBoard boardRef;
			boardRef.initializeGame();
			ChessBoard board;
			board.initializeGame();
			board.performMove(Move(Position(4, 1), Position(4, 3)));
			board.takeBackLastMove();
			TEST_ASSERT(board.sideToMove() == WHITE);
			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 8; j++) 
				{
					TEST_ASSERT(boardRef.get(i, j) == board.get(i, j));
				}
			}

			boardRef.initializeGame();
			board.initializeGame();
			board.performMove(Move(Position(4, 1), Position(4, 3))); // e4
			board.performMove(Move(Position(4, 6), Position(4, 4))); // e5
			board.performMove(Move(Position(5, 0), Position(1, 3))); // Bb4
			board.performMove(Move(Position(5, 7), Position(1, 4))); // Bb5
			board.performMove(Move(Position(6, 0), Position(5, 2))); // Nf3
			board.performMove(Move(Position(6, 7), Position(5, 5))); // Nf6
			board.performMove(Move(Position(4, 0), Position(6, 0))); // O-O
			board.takeBackLastMove(); // O-O
			TEST_ASSERT(board.sideToMove() == WHITE);
			board.takeBackLastMove(); // Nf6
			TEST_ASSERT(board.sideToMove() == BLACK);
			board.takeBackLastMove(); // Nf3
			TEST_ASSERT(board.sideToMove() == WHITE);
			board.takeBackLastMove(); // Bb5
			TEST_ASSERT(board.sideToMove() == BLACK);
			board.takeBackLastMove(); // Bb4
			TEST_ASSERT(board.sideToMove() == WHITE);
			board.takeBackLastMove(); // e5
			TEST_ASSERT(board.sideToMove() == BLACK);
			board.takeBackLastMove(); // e4
			TEST_ASSERT(board.sideToMove() == WHITE);

			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 8; j++) 
				{
					TEST_ASSERT(boardRef.get(i, j) == board.get(i, j));
				}
			}
		}

		/*
		   void RecognizeMoves ()
		   {
		   Move mov(Position(0, 0), Position(0, 0));
		// Normal moves
		TEST_ASSERT(recognizeAsMove("e2e4", &mov));
		TEST_ASSERT(mov == Move(Position(4, 1), Position(4, 3)));
		TEST_ASSERT(!recognizeAsMove("e2", &mov));

		// Promotion
		TEST_ASSERT(recognizeAsMove("e7e8q", &mov));
		TEST_ASSERT(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_QUEEN));
		TEST_ASSERT(recognizeAsMove("e7e8r", &mov));
		TEST_ASSERT(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_ROOK));
		TEST_ASSERT(recognizeAsMove("e7e8n", &mov));
		TEST_ASSERT(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_KNIGHT));
		TEST_ASSERT(recognizeAsMove("e7e8b", &mov));
		TEST_ASSERT(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_BISHOP));

		}
		 */
};

