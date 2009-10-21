#include "stdafx.h"
#include "chessboard.h"

ChessBoard::ChessBoard()
{

}

void ChessBoard::initializeGame()
{
	toMove = WHITE;

	// Position white officers
	board[0][0] = WHITE_ROOK;
	board[1][0] = WHITE_KNIGHT;
	board[2][0] = WHITE_BISHOP;
	board[3][0] = WHITE_QUEEN;
	board[4][0] = WHITE_KING;
	board[5][0] = WHITE_BISHOP;
	board[6][0] = WHITE_KNIGHT;
	board[7][0] = WHITE_ROOK;

	// Position white pawns
	board[0][1] = WHITE_PAWN;
	board[1][1] = WHITE_PAWN;
	board[2][1] = WHITE_PAWN;
	board[3][1] = WHITE_PAWN;
	board[4][1] = WHITE_PAWN;
	board[5][1] = WHITE_PAWN;
	board[6][1] = WHITE_PAWN;
	board[7][1] = WHITE_PAWN;

	// Position black pawns
	board[0][6] = BLACK_PAWN;
	board[1][6] = BLACK_PAWN;
	board[2][6] = BLACK_PAWN;
	board[3][6] = BLACK_PAWN;
	board[4][6] = BLACK_PAWN;
	board[5][6] = BLACK_PAWN;
	board[6][6] = BLACK_PAWN;
	board[7][6] = BLACK_PAWN;

	// Position black officers
	board[0][7] = BLACK_ROOK;
	board[1][7] = BLACK_KNIGHT;
	board[2][7] = BLACK_BISHOP;
	board[3][7] = BLACK_QUEEN;
	board[4][7] = BLACK_KING;
	board[5][7] = BLACK_BISHOP;
	board[6][7] = BLACK_KNIGHT;
	board[7][7] = BLACK_ROOK;

}

Pieces ChessBoard::get(int column, int row)
{
	return board[column][row];
}

Side ChessBoard::sideToMove()
{
	return toMove;
}