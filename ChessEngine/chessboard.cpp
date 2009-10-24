#include "stdafx.h"
#include "chessboard.h"
#include <assert.h>

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

	for(int i = 0; i < 8; i++)
	{
		for(int j = 2; j < 6; j++)
		{
			board[i][j] = NO_PIECE;
		}
	}

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

void ChessBoard::performMove(int column0, int row0, int column1, int row1)
{
	board[column1][row1] = board[column0][row0];
	board[column0][row0] = NO_PIECE;

	if(toMove == WHITE)
	{
		toMove = BLACK;
	}
	else
	{
		toMove = WHITE;
	}
}

bool ChessBoard::isWhiteKingUnderAttack()
{
	std::pair <int, int> posOfWhiteKing = locateWhiteKing();
	int column = posOfWhiteKing.first;
	int row = posOfWhiteKing.second;

	Pieces nearest;
	// Above
	nearest = firstPieceInDirection(column, row, 0, 1);
	if(nearest == BLACK_ROOK)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;
	// Below
	nearest = firstPieceInDirection(column, row, 0, -1);
	if(nearest == BLACK_ROOK)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;
	// Left
	nearest = firstPieceInDirection(column, row, -1, 0);
	if(nearest == BLACK_ROOK)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;
	// Right
	nearest = firstPieceInDirection(column, row, 1, 0);
	if(nearest == BLACK_ROOK)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;
	// Above right
	nearest = firstPieceInDirection(column, row, 1, 1);
	if(nearest == BLACK_BISHOP)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;
	// Above left
	nearest = firstPieceInDirection(column, row, 1, -1);
	if(nearest == BLACK_BISHOP)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;
	// Below right
	nearest = firstPieceInDirection(column, row, -1, 1);
	if(nearest == BLACK_BISHOP)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;
	// Below left
	nearest = firstPieceInDirection(column, row, -1, -1);
	if(nearest == BLACK_BISHOP)
		return true;
	if(nearest == BLACK_QUEEN)
		return true;

	return false;
}

bool ChessBoard::isBlackKingUnderAttack()
{
	return false;
}

void ChessBoard::clearBoard()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			board[i][j] = NO_PIECE;
	
	toMove = WHITE;
}

void ChessBoard::placePiece(int column, int row, Pieces piece)
{
	board[column][row] = piece;
}

void ChessBoard::setSideToMove(Side side)
{
	toMove = side;
}

Pieces ChessBoard::firstPieceInDirection(int column, int row, int dirColumn, int dirRow)
{
	for(int i = 1; i < 8; i++)
	{
		int testColumn = column + i * dirColumn;
		int testRow = row + i * dirRow;

		if(testColumn < 0 || testColumn > 7)
			break;

		if(testRow < 0 || testRow > 7)
			break;

		if(board[testColumn][testRow] != NO_PIECE)
			return board[testColumn][testRow];
	}

	return NO_PIECE;
}

std::pair <int, int> ChessBoard::locateWhiteKing()
{
	// Locate position of the white king
	int column = -1;
	int row = -1;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j] == WHITE_KING)
			{
				column = i;
				row = j;
			}
		}
	}

	assert(column != -1);
	return std::make_pair(column, row);
}

std::pair <int, int> ChessBoard::locateBlackKing()
{
	// Locate position of the white king
	int column = -1;
	int row = -1;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j] == BLACK_KING)
			{
				column = i;
				row = j;
			}
		}
	}

	assert(column != -1);
	return std::make_pair(column, row);
}