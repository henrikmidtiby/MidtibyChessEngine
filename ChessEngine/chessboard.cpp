#include "stdafx.h"
#include "chessboard.h"
#include <assert.h>

int kingMovesColumn[8] = { 0, -1, -1, -1,  0,  1,  1,  1};
int kingMovesRow[8]    = { 1,  1,  0, -1, -1, -1,  0,  1};

int knightMovesColumn[8] = { -1, -2, -2, -1,  1,  2,  2,  1};
int knightMovesRow[8]    = {  2,  1, -1, -2, -2, -1,  1,  2};

int rookDirectionsColumn[4] = { 1,  0, -1,  0};
int rookDirectionsRow[4]    = { 0, -1,  0,  1};

int bishopDirectionsColumn[4] = { 1,  1, -1, -1};
int bishopDirectionsRow[4]    = { 1, -1, -1,  1};

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
	if(column < 0 || column > 7)
		return OUTSIDE_BOARD;
	if(row < 0 || row > 7)
		return OUTSIDE_BOARD;
	return board[column][row];
}

Side ChessBoard::sideToMove()
{
	return toMove;
}

void ChessBoard::performMove(Position pos0, Position pos1)
{
	board[pos1.column][pos1.row] = board[pos0.column][pos0.row];
	board[pos0.column][pos0.row] = NO_PIECE;

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
	Position posOfWhiteKing = locateWhiteKing();
	return isLocationAttackedByBlackPieces(posOfWhiteKing);
}

bool ChessBoard::isLocationAttackedByBlackPieces(Position pos)
{
	int column = pos.column;
	int row = pos.row;
	Pieces nearest;

	// Look for rook like attacks
	for(int i = 0; i < 8; i++)
	{
		nearest = firstPieceInDirection(pos, rookDirectionsColumn[i], rookDirectionsRow[i]);
		if(nearest == BLACK_ROOK)
			return true;
		if(nearest == BLACK_QUEEN)
			return true;
	}

	// Look for bishop like attacks
	for(int i = 0; i < 8; i++)
	{
		nearest = firstPieceInDirection(pos, bishopDirectionsColumn[i], bishopDirectionsRow[i]);
		if(nearest == BLACK_BISHOP)
			return true;
		if(nearest == BLACK_QUEEN)
			return true;
	}

	// Look for knight attacks
	for(int i = 0; i < 8; i++)
	{
		if(get(column + knightMovesColumn[i], row + knightMovesRow[i]) == BLACK_KNIGHT)
			return true;
	}

	// Look for pawn attacks
	if(get(column + 1, row + 1) == BLACK_PAWN)
		return true;
	if(get(column - 1, row + 1) == BLACK_PAWN)
		return true;

	// Look for king attacks
	for(int i = 0; i < 8; i++)
	{
		if(get(column + kingMovesColumn[i], row + kingMovesRow[i]) == BLACK_KING)
			return true;
	}

	return false;
}

bool ChessBoard::isLocationAttackedByWhitePieces(Position pos)
{
	int column = pos.column;
	int row = pos.row;
	Pieces nearest;

	// Look for rook like attacks
	for(int i = 0; i < 8; i++)
	{
		nearest = firstPieceInDirection(pos, rookDirectionsColumn[i], rookDirectionsRow[i]);
		if(nearest == WHITE_ROOK)
			return true;
		if(nearest == WHITE_QUEEN)
			return true;
	}

	// Look for bishop like attacks
	for(int i = 0; i < 8; i++)
	{
		nearest = firstPieceInDirection(pos, bishopDirectionsColumn[i], bishopDirectionsRow[i]);
		if(nearest == WHITE_BISHOP)
			return true;
		if(nearest == WHITE_QUEEN)
			return true;
	}

	// Look for knight attacks
	for(int i = 0; i < 8; i++)
	{
		if(get(column + knightMovesColumn[i], row + knightMovesRow[i]) == WHITE_KNIGHT)
			return true;
	}

	// Look for pawn attacks
	if(get(column + 1, row - 1) == WHITE_PAWN)
		return true;
	if(get(column - 1, row - 1) == WHITE_PAWN)
		return true;

	// Look for king attacks
	for(int i = 0; i < 8; i++)
	{
		if(get(column + kingMovesColumn[i], row + kingMovesRow[i]) == WHITE_KING)
			return true;
	}

	return false;
}

bool ChessBoard::isBlackKingUnderAttack()
{
	Position posOfWhiteKing = locateBlackKing();
	return isLocationAttackedByWhitePieces(posOfWhiteKing);
}

void ChessBoard::clearBoard()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			board[i][j] = NO_PIECE;
	
	toMove = WHITE;
}

void ChessBoard::placePiece(Position pos, Pieces piece)
{
	board[pos.column][pos.row] = piece;
}

void ChessBoard::setSideToMove(Side side)
{
	toMove = side;
}

Pieces ChessBoard::firstPieceInDirection(Position pos, int dirColumn, int dirRow)
{
	int column = pos.column;
	int row = pos.row;

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

Position ChessBoard::locateWhiteKing()
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
	return Position(column, row);
}

Position ChessBoard::locateBlackKing()
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
	return Position(column, row);
}

std::vector<Move> ChessBoard::PossibleMoves()
{
	if(toMove == WHITE)
	{
		return PossibleWhiteMoves();
	}
}

std::vector<Move> ChessBoard::PossibleWhiteMoves()
{
	std::vector<Move> moves;
	
	for(int column = 0; column < 8; column++)
	{
		for(int row = 0; row < 8; row++)
		{
			if(board[column][row] == WHITE_PAWN)
			{
				moveLikeWhitePawn(column, row, moves);
			}
			if(board[column][row] == WHITE_ROOK)
			{
				moveLikeWhiteRook(column, row, moves);
			}
			if(board[column][row] == WHITE_BISHOP)
			{
				moveLikeWhiteBishop(column, row, moves);
			}
			if(board[column][row] == WHITE_QUEEN)
			{
				moveLikeWhiteRook(column, row, moves);
				moveLikeWhiteBishop(column, row, moves);
			}			
			if(board[column][row] == WHITE_KING)
			{
				moveLikeWhiteKing(column, row, moves);
			}
		}
	}
	return moves;
}


bool ChessBoard::isBlackPiece(Pieces piece)
{
	if(piece == BLACK_PAWN)
		return true;
	if(piece == BLACK_ROOK)
		return true;
	if(piece == BLACK_KNIGHT)
		return true;
	if(piece == BLACK_BISHOP)
		return true;
	if(piece == BLACK_QUEEN)
		return true;
	if(piece == BLACK_KING)
		return true;

	return false;
}

bool ChessBoard::isWhitePiece(Pieces piece)
{
	if(piece == WHITE_PAWN)
		return true;
	if(piece == WHITE_ROOK)
		return true;
	if(piece == WHITE_KNIGHT)
		return true;
	if(piece == WHITE_BISHOP)
		return true;
	if(piece == WHITE_QUEEN)
		return true;
	if(piece == WHITE_KING)
		return true;

	return false;
}

bool ChessBoard::isWhiteOrEmpty(Pieces piece)
{
	if(isWhitePiece(piece))
		return true;
	if(piece == NO_PIECE)
		return true;
	
	return false;
}

bool ChessBoard::isBlackOrEmpty(Pieces piece)
{
	if(isBlackPiece(piece))
		return true;
	if(piece == NO_PIECE)
		return true;

	return false;
}

bool ChessBoard::isOutsideBoard(Position pos)
{
	if(pos.column < 0)
		return true;
	if(pos.column > 7)
		return true;
	if(pos.row < 0)
		return true;
	if(pos.row > 7)
		return true;

	return false;
}

void ChessBoard::moveWhitePieceInLine( int column, int row, int dcolumn, int drow, std::vector<Move> &moves )
{
	for(int i = 1; i < 8; i++)
	{	
		if(isOutsideBoard(Position(column + i*dcolumn, row + i*drow)))
			break;
		if(isBlackOrEmpty(board[column + i*dcolumn][row + i*drow]))
			moves.push_back((Move(column, row, column+i*dcolumn, row + i*drow)));
		if(get(column+i*dcolumn, row + i*drow) != NO_PIECE)
			break;
	}
}

void ChessBoard::moveLikeWhiteRook( int column, int row, std::vector<Move> &moves )
{
	moveWhitePieceInLine(column, row,  0,  1, moves);
	moveWhitePieceInLine(column, row,  0, -1, moves);
	moveWhitePieceInLine(column, row,  1,  0, moves);
	moveWhitePieceInLine(column, row, -1,  0, moves);
}

void ChessBoard::moveLikeWhiteBishop( int column, int row, std::vector<Move> &moves )
{
	moveWhitePieceInLine(column, row,  1,  1, moves);
	moveWhitePieceInLine(column, row,  1, -1, moves);
	moveWhitePieceInLine(column, row, -1,  1, moves);
	moveWhitePieceInLine(column, row, -1, -1, moves);
}

void ChessBoard::moveLikeWhitePawn( int column, int row, std::vector<Move> &moves )
{
	if(board[column][row + 1] == NO_PIECE)
	{
		moves.push_back(Move(column, row, column, row + 1));
		if(row == 1 && board[column][row + 2] == NO_PIECE)
			moves.push_back(Move(column, row, column, row + 2));
	}
	if(isBlackPiece(board[column - 1][row + 1]))
		moves.push_back(Move(column, row, column - 1, row + 1));
	if(isBlackPiece(board[column + 1][row + 1]))
		moves.push_back(Move(column, row, column + 1, row + 1));
}

void ChessBoard::moveLikeWhiteKing( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isBlackOrEmpty(get(column + kingMovesColumn[i], row + kingMovesRow[i])))
			moves.push_back(Move(column, row, column + kingMovesColumn[i], row + kingMovesRow[i]));
	}
}