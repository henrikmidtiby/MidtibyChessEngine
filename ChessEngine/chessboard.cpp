#include "stdafx.h"
#include "chessboard.h"
#include <assert.h>
#include <algorithm>
#include <string>

#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )


// Stolen from tscp181
int pawn_pcsq[64] = {
	  0,   0,   0,   0,   0,   0,   0,   0,
	  5,  10,  15,  20,  20,  15,  10,   5,
	  4,   8,  12,  16,  16,  12,   8,   4,
	  3,   6,   9,  12,  12,   9,   6,   3,
	  2,   4,   6,   8,   8,   6,   4,   2,
	  1,   2,   3, -10, -10,   3,   2,   1,
	  0,   0,   0, -40, -40,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0
};

int king_pcsq[64] = {
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-40, -40, -40, -40, -40, -40, -40, -40,
	-20, -20, -20, -20, -20, -20, -20, -20,
	  0,  20,  40, -20,   0, -20,  40,  20
};


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
	whiteCastleKing = true;
	whiteCastleQueen = true;
	blackCastleKing = true;
	blackCastleQueen = true;
	bestMove = Move(0, 0, 0, 0, STANDARD_MOVE);
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

Pieces ChessBoard::get(Position pos)
{
	return get(pos.column, pos.row);
}

Side ChessBoard::sideToMove()
{
	return toMove;
}

void ChessBoard::performMove(Move mov)
{
	history.push_back(mov);
	captures.push_back(board[mov.to.column][mov.to.row]);

	performMoveWrapper(mov);

	// Remove castling rights
	if(board[0][0] != WHITE_ROOK)
		whiteCastleQueen = false;
	if(board[7][0] != WHITE_ROOK)
		whiteCastleKing = false;
	if(board[4][0] != WHITE_KING)
	{
		whiteCastleKing = false;
		whiteCastleQueen = false;
	}

	if(board[0][7] != BLACK_ROOK)
		blackCastleQueen = false;
	if(board[7][7] != BLACK_ROOK)
		blackCastleKing = false;
	if(board[4][7] != BLACK_KING)
	{
		blackCastleKing = false;
		blackCastleQueen = false;
	}
}

void ChessBoard::performMoveWrapper(Move mov)
{
	if(get(mov.from) == OUTSIDE_BOARD || get(mov.to) == OUTSIDE_BOARD)
	{
		assert(false);
	}


	if(toMove == WHITE)
	{
		toMove = BLACK;
	}
	else
	{
		toMove = WHITE;
	}

	if(mov.notice == STANDARD_MOVE)
	{
		// Detect casteling
		if(mov.from.column == 4 
			&& mov.from.row == 0 
			&& mov.to.row == 0
			&& board[mov.from.column][mov.from.row] == WHITE_KING)
		{
			if(mov.to.column == 2)
			{
				// Queen side
				board[4][0] = NO_PIECE;
				board[0][0] = NO_PIECE;
				board[2][0] = WHITE_KING;
				board[3][0] = WHITE_ROOK;
				return;
			}
			if(mov.to.column == 6)
			{
				// King side
				board[4][0] = NO_PIECE;
				board[7][0] = NO_PIECE;
				board[6][0] = WHITE_KING;
				board[5][0] = WHITE_ROOK;
				return;
			}

		}
		// Detect casteling
		if(mov.from.column == 4 
			&& mov.from.row == 7 
			&& mov.to.row == 7
			&& board[mov.from.column][mov.from.row] == BLACK_KING)
		{
			if(mov.to.column == 2)
			{
				// Queen side
				board[4][7] = NO_PIECE;
				board[0][7] = NO_PIECE;
				board[2][7] = BLACK_KING;
				board[3][7] = BLACK_ROOK;
				return;
			}
			if(mov.to.column == 6)
			{
				// King side
				board[4][7] = NO_PIECE;
				board[7][7] = NO_PIECE;
				board[6][7] = BLACK_KING;
				board[5][7] = BLACK_ROOK;
				return;
			}

		}
		board[mov.to.column][mov.to.row] = board[mov.from.column][mov.from.row];
		board[mov.from.column][mov.from.row] = NO_PIECE;
	}
	else if(mov.notice == PROMOTE_TO_QUEEN)
	{
		if(toMove == BLACK)
		{
			board[mov.to.column][mov.to.row] = WHITE_QUEEN;
		}
		else
		{
			board[mov.to.column][mov.to.row] = BLACK_QUEEN;
		}
		board[mov.from.column][mov.from.row] = NO_PIECE;
	}
	else if(mov.notice == PROMOTE_TO_ROOK)
	{
		if(toMove == BLACK)
		{
			board[mov.to.column][mov.to.row] = WHITE_ROOK;
		}
		else
		{
			board[mov.to.column][mov.to.row] = BLACK_ROOK;
		}
		board[mov.from.column][mov.from.row] = NO_PIECE;
	}
	else if(mov.notice == PROMOTE_TO_KNIGHT)
	{
		if(toMove == BLACK)
		{
			board[mov.to.column][mov.to.row] = WHITE_KNIGHT;
		}
		else
		{
			board[mov.to.column][mov.to.row] = BLACK_KNIGHT;
		}
		board[mov.from.column][mov.from.row] = NO_PIECE;
	}
	else if(mov.notice == PROMOTE_TO_BISHOP)
	{
		if(toMove == BLACK)
		{
			board[mov.to.column][mov.to.row] = WHITE_BISHOP;
		}
		else
		{
			board[mov.to.column][mov.to.row] = BLACK_BISHOP;
		}
		board[mov.from.column][mov.from.row] = NO_PIECE;
	}

}


void ChessBoard::performMove(Position pos0, Position pos1)
{
	performMove(Move(pos0, pos1));
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
	for(int i = 0; i < 4; i++)
	{
		nearest = firstPieceInDirection(pos, rookDirectionsColumn[i], rookDirectionsRow[i]);
		if(nearest == BLACK_ROOK)
			return true;
		if(nearest == BLACK_QUEEN)
			return true;
	}

	// Look for bishop like attacks
	for(int i = 0; i < 4; i++)
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
	for(int i = 0; i < 4; i++)
	{
		nearest = firstPieceInDirection(pos, rookDirectionsColumn[i], rookDirectionsRow[i]);
		if(nearest == WHITE_ROOK)
			return true;
		if(nearest == WHITE_QUEEN)
			return true;
	}

	// Look for bishop like attacks
	for(int i = 0; i < 4; i++)
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
	Position posOfBlackKing = locateBlackKing();
	return isLocationAttackedByWhitePieces(posOfBlackKing);
}

void ChessBoard::clearBoard()
{
	whiteCastleKing = false;
	whiteCastleQueen = false;
	blackCastleKing = false;
	blackCastleQueen = false;
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

std::vector<Move> ChessBoard::possibleMoves()
{
	if(toMove == WHITE)
	{
		return possibleWhiteMoves();
	}
	else
	{
		return possibleBlackMoves();
	}
}

std::vector<Move> ChessBoard::possibleWhiteMoves()
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
			if(board[column][row] == WHITE_KNIGHT)
			{
				moveLikeWhiteKnight(column, row, moves);
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
				whiteCastling(moves);
			}
		}
	}


	return moves;
}


bool ChessBoard::isBlackPiece(Pieces piece)
{
	
	if(piece > OUTSIDE_BOARD)
		return true;
	else
		return false;
}

bool ChessBoard::isWhitePiece(Pieces piece)
{
	if(piece < NO_PIECE)
		return true;
	else
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

inline void ChessBoard::moveWhitePieceInLine( int column, int row, int dcolumn, int drow, std::vector<Move> &moves )
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

inline void ChessBoard::moveLikeWhiteRook( int column, int row, std::vector<Move> &moves )
{
	moveWhitePieceInLine(column, row,  0,  1, moves);
	moveWhitePieceInLine(column, row,  0, -1, moves);
	moveWhitePieceInLine(column, row,  1,  0, moves);
	moveWhitePieceInLine(column, row, -1,  0, moves);
}

inline void ChessBoard::moveLikeWhiteBishop( int column, int row, std::vector<Move> &moves )
{
	moveWhitePieceInLine(column, row,  1,  1, moves);
	moveWhitePieceInLine(column, row,  1, -1, moves);
	moveWhitePieceInLine(column, row, -1,  1, moves);
	moveWhitePieceInLine(column, row, -1, -1, moves);
}

inline void ChessBoard::promotePawnMove(Position from, Position to, std::vector<Move> &moves)
{
	moves.push_back(Move(from, to, PROMOTE_TO_QUEEN));
	moves.push_back(Move(from, to, PROMOTE_TO_ROOK));
	moves.push_back(Move(from, to, PROMOTE_TO_KNIGHT));
	moves.push_back(Move(from, to, PROMOTE_TO_BISHOP));
}

void ChessBoard::moveLikeWhitePawn( int column, int row, std::vector<Move> &moves )
{
	if(row == 6)
	{
		// The pawn will be promoted
		if(board[column][row + 1] == NO_PIECE)
		{
			promotePawnMove(Position(column, row), Position(column, row + 1), moves);
		}
		if(isBlackPiece(get(column - 1, row + 1)))
		{
			promotePawnMove(Position(column, row), Position(column - 1, row + 1), moves);
		}
		if(isBlackPiece(get(column + 1, row + 1)))
		{
			promotePawnMove(Position(column, row), Position(column + 1, row + 1), moves);
		}
	}
	else
	{
		if(get(column, row + 1) == NO_PIECE)
		{
			moves.push_back(Move(column, row, column, row + 1));
			if(row == 1 && get(column, row + 2) == NO_PIECE)
				moves.push_back(Move(column, row, column, row + 2));
		}
		if(isBlackPiece(get(column - 1, row + 1)))
			moves.push_back(Move(column, row, column - 1, row + 1));
		if(isBlackPiece(get(column + 1, row + 1)))
			moves.push_back(Move(column, row, column + 1, row + 1));
	}
}

inline void ChessBoard::moveLikeWhiteKing( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isBlackOrEmpty(get(column + kingMovesColumn[i], row + kingMovesRow[i])))
			moves.push_back(Move(column, row, column + kingMovesColumn[i], row + kingMovesRow[i]));
	}
}

inline void ChessBoard::moveLikeWhiteKnight( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isBlackOrEmpty(get(column + knightMovesColumn[i], row + knightMovesRow[i])))
			moves.push_back(Move(column, row, column + knightMovesColumn[i], row + knightMovesRow[i]));
	}
}

std::vector<Move> ChessBoard::possibleBlackMoves()
{
	std::vector<Move> moves;

	for(int column = 0; column < 8; column++)
	{
		for(int row = 0; row < 8; row++)
		{
			if(board[column][row] == BLACK_PAWN)
			{
				moveLikeBlackPawn(column, row, moves);
			}
			if(board[column][row] == BLACK_ROOK)
			{
				moveLikeBlackRook(column, row, moves);
			}
			if(board[column][row] == BLACK_KNIGHT)
			{
				moveLikeBlackKnight(column, row, moves);
			}
			if(board[column][row] == BLACK_BISHOP)
			{
				moveLikeBlackBishop(column, row, moves);
			}
			if(board[column][row] == BLACK_KING)
			{
				moveLikeBlackKing(column, row, moves);
				blackCastling(moves);
			}
			if(board[column][row] == BLACK_QUEEN)
			{
				moveLikeBlackBishop(column, row, moves);
				moveLikeBlackRook(column, row, moves);
			}
		}
	}
	return moves;
}

inline void ChessBoard::moveLikeBlackKnight( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isWhiteOrEmpty(get(column + knightMovesColumn[i], row + knightMovesRow[i])))
			moves.push_back(Move(column, row, column + knightMovesColumn[i], row + knightMovesRow[i]));
	}
}

inline void ChessBoard::moveLikeBlackPawn( int column, int row, std::vector<Move> &moves )
{
	if(row == 1)
	{
		if(get(column, row - 1) == NO_PIECE)
			promotePawnMove(Position(column, row), Position(column, row - 1), moves);
		if(isWhitePiece(get(column - 1, row - 1)))
			promotePawnMove(Position(column, row), Position(column - 1, row - 1), moves);
		if(isWhitePiece(get(column + 1, row - 1)))
			promotePawnMove(Position(column, row), Position(column + 1, row - 1), moves);
	}
	else
	{
		if(board[column][row - 1] == NO_PIECE)
		{
			moves.push_back(Move(column, row, column, row - 1));
			if(row == 6 && get(column, row - 2) == NO_PIECE)
				moves.push_back(Move(column, row, column, row - 2));
		}
		if(isWhitePiece(get(column - 1, row - 1)))
			moves.push_back(Move(column, row, column - 1, row - 1));
		if(isWhitePiece(get(column + 1, row - 1)))
			moves.push_back(Move(column, row, column + 1, row - 1));
	}
}

inline void ChessBoard::moveLikeBlackKing( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isWhiteOrEmpty(get(column + kingMovesColumn[i], row + kingMovesRow[i])))
			moves.push_back(Move(column, row, column + kingMovesColumn[i], row + kingMovesRow[i]));
	}
}

inline void ChessBoard::moveBlackPieceInLine( int column, int row, int dcolumn, int drow, std::vector<Move> &moves )
{
	for(int i = 1; i < 8; i++)
	{	
		if(isOutsideBoard(Position(column + i*dcolumn, row + i*drow)))
			break;
		if(isWhiteOrEmpty(board[column + i*dcolumn][row + i*drow]))
			moves.push_back((Move(column, row, column+i*dcolumn, row + i*drow)));
		if(get(column+i*dcolumn, row + i*drow) != NO_PIECE)
			break;
	}
}

inline void ChessBoard::moveLikeBlackRook( int column, int row, std::vector<Move> &moves )
{
	moveBlackPieceInLine(column, row,  0,  1, moves);
	moveBlackPieceInLine(column, row,  0, -1, moves);
	moveBlackPieceInLine(column, row,  1,  0, moves);
	moveBlackPieceInLine(column, row, -1,  0, moves);
}

inline void ChessBoard::moveLikeBlackBishop( int column, int row, std::vector<Move> &moves )
{
	moveBlackPieceInLine(column, row,  1,  1, moves);
	moveBlackPieceInLine(column, row,  1, -1, moves);
	moveBlackPieceInLine(column, row, -1,  1, moves);
	moveBlackPieceInLine(column, row, -1, -1, moves);
}

std::vector<Move> ChessBoard::legalMoves()
{
	std::vector<Move> moves = possibleMoves();
	std::vector<Move> legalMovesList;
	if(toMove == WHITE)
	{
		for(int i = 0; i < (int) moves.size(); i++)
		{
			Move curMove = moves.at(i);
			ChessBoard tempPos(*this);
			tempPos.performMove(curMove.from, curMove.to);
			if(!tempPos.isWhiteKingUnderAttack())
			{
				legalMovesList.push_back(curMove);
			}
		}
	}
	else
	{
		for(int i = 0; i < (int) moves.size(); i++)
		{
			Move curMove = moves.at(i);
			ChessBoard tempPos(*this);
			tempPos.performMove(curMove.from, curMove.to);
			if(!tempPos.isBlackKingUnderAttack())
			{
				legalMovesList.push_back(curMove);
			}
		}
	}

	return legalMovesList;
}

char ChessBoard::encodePiece(Pieces piece)
{
	if(piece == NO_PIECE)
		return ' ';
	if(piece == WHITE_PAWN)
		return 'P';
	if(piece == WHITE_ROOK)
		return 'R';
	if(piece == WHITE_KNIGHT)
		return 'N';
	if(piece == WHITE_BISHOP)
		return 'B';
	if(piece == WHITE_QUEEN)
		return 'Q';
	if(piece == WHITE_KING)
		return 'K';
	if(piece == BLACK_PAWN)
		return 'p';
	if(piece == BLACK_ROOK)
		return 'r';
	if(piece == BLACK_KNIGHT)
		return 'n';
	if(piece == BLACK_BISHOP)
		return 'b';
	if(piece == BLACK_QUEEN)
		return 'q';
	if(piece == BLACK_KING)
		return 'k';
	assert(1 != 2);
	return 'x';
}

void ChessBoard::printBoard()
{
	if(toMove == WHITE)
		printf("White to move\n");
	else
		printf("Black to move\n");

	for(int row = 7; row > -1; row--)
	{
		printf("%d ", row + 1);
		for(int column = 0; column < 8; column++)
		{
			Pieces temp = board[column][row];
			if(temp == NO_PIECE)
			{
				if((column + row) % 2 == 1)
				{
					printf("# ");
				}
				else
				{
					printf("  ");
				}
			}
			else
			{
				printf("%c ", encodePiece(temp));
			}
		}
		printf("\n");
	}
	printf("  a b c d e f g h\n");
}

void ChessBoard::printMovesFromList(std::vector<Move> moves)
{
	for(int i = 0; i < (int) moves.size(); i++)
	{
		Move mov = moves.at(i);
		printf("%2d: %s\n", i + 1, mov.toString().c_str());
	}
}

bool ChessBoard::isBlackMate()
{
	if(isBlackKingUnderAttack())
	{
		if(!isThereLegalMovesAvailable())
		{
			return true;
		}
	}	

	return false;
}

bool ChessBoard::isWhiteMate()
{
	if(isWhiteKingUnderAttack())
	{
		if(!isThereLegalMovesAvailable())
		{
			return true;
		}
	}
	return false;
}

bool ChessBoard::isThereLegalMovesAvailable()
{
	std::vector<Move> moves = legalMoves();
	if(moves.size() == 0)
	{
		return false;
	}
	return true;
}

double ChessBoard::pieceValue(Pieces piece)
{
	if(piece == WHITE_KING) return  0;
	if(piece == BLACK_KING) return  0;
	if(piece == WHITE_QUEEN) return  900;
	if(piece == BLACK_QUEEN) return -900;
	if(piece == WHITE_ROOK) return  500;
	if(piece == BLACK_ROOK) return -500;
	if(piece == WHITE_KNIGHT) return  300;
	if(piece == BLACK_KNIGHT) return -300;
	if(piece == WHITE_BISHOP) return  300;
	if(piece == BLACK_BISHOP) return -300;
	if(piece == WHITE_PAWN) return  100;
	if(piece == BLACK_PAWN) return -100;
	return 0;
}

double ChessBoard::basicMaterialCount()
{
	material = 0;
	totalMaterial = 0;
	for(int column = 0; column < 8; column++)
		for(int row = 0; row < 8; row++)
		{	
			double temp = pieceValue(get(column, row));
			material += temp;
			totalMaterial += abs(temp);
		}
	return material * ( 1 + 10 / totalMaterial);
}


double ChessBoard::piecePositionBonus(Pieces piece, int column, int row)
{
	if(piece == WHITE_PAWN)
	{
		return pawn_pcsq[column + 8 * (7-row)];
	}
	if(piece == BLACK_PAWN)
	{
		return -pawn_pcsq[column + 8 * (row)];
	}

	if(piece == WHITE_BISHOP || piece == WHITE_KNIGHT)
	{
		return 10 - 2*abs(column - 3.5) - 2*abs(row - 3.5);
	}
	if(piece == BLACK_BISHOP || piece == BLACK_KNIGHT)
	{
		return -1*(10 - 2*abs(column - 3.5) - 2*abs(row - 3.5));
	}

	// Crude check for endgame 
	if(totalMaterial < 3900)
	{
		if(piece == WHITE_PAWN)
		{
			return 5*row;	
		}
		if(piece == BLACK_PAWN)
		{
			return 5*(7-row);	
		}

		if(piece == WHITE_KING)
		{
			return -((row - 3.5)*(row - 3.5) + (column - 3.5)*(column - 3.5));
		}
		if(piece == BLACK_KING)
		{
			return ((row - 3.5)*(row - 3.5) + (column - 3.5)*(column - 3.5));
		}
	}
	else
	{
		// Not in endgame
		if(piece == WHITE_KING)
		{
			return king_pcsq[column + 8*(7-row)];
		}
		if(piece == BLACK_KING)
		{
			return king_pcsq[column + 8*(row)];
		}
	}
	return 0;
}

double ChessBoard::positionBonusses()
{
	double bonus = 0;
	for(int column = 0; column < 8; column++)
	{
		for(int row = 0; row < 8; row++)
		{	
			double temp = piecePositionBonus(get(column, row), column, row);
			bonus += temp;
		}
	}
	return bonus;
}


double ChessBoard::pawnStructureBonus()
{
	double bonus = 0;

	// Locate pawns in both colors (the one closest to the initial position)
	char pawns[2][8];
	for(int i = 0; i < 8; i++)
	{
		pawns[0][i] = 0;
		pawns[1][i] = 0;
	}

	for(int column = 0; column < 8; column++)
	{
		// Look for white pawns
		for(int row = 0; row < 8; row++)
		{
			if(board[column][row] == WHITE_PAWN)
			{
				if(pawns[0][column] != 0)
				{
					bonus -= DOUBLED_PAWNS_PENALTY;
				}
				pawns[0][column] = row;
			}
		}

		// Look for black pawns
		for(int row = 7; row > 0; row--)
		{
			if(board[column][row] == BLACK_PAWN)
			{
				if(pawns[1][column] != 0)
				{
					bonus += DOUBLED_PAWNS_PENALTY;
				}
				pawns[1][column] = row;
			}
		}
	}

	for(int column = 0; column < 8; column++)
	{
		for(int row = 0; row < 8; row++)
		{
			if(board[column][row] == WHITE_PAWN)
			{
				// Detect isolated pawns
				if(column == 0 || pawns[0][column - 1] == 0)
				{
					if(column == 7 || pawns[0][column + 1] == 0)
					{
						bonus -= ISOLATED_PAWN;
					}
				}

				// Detect passed pawn
				if(column == 0 || pawns[1][column - 1] <= row)
				{
					if(column == 7 || pawns[1][column + 1] <= row)
					{
						bonus += PASSED_PAWN_BONUS;
					}
				}
			}

			if(board[column][row] == BLACK_PAWN)
			{
				// Detect isolated pawns
				if(column == 0 || pawns[1][column - 1] == 0)
				{
					if(column == 7 || pawns[1][column + 1] == 0)
					{
						bonus += ISOLATED_PAWN;
					}
				}

				// Detect passed pawn
				if(column == 0 || pawns[0][column - 1] >= row)
				{
					if(column == 7 || pawns[0][column + 1] >= row)
					{
						bonus -= PASSED_PAWN_BONUS;
					}
				}
			}
		}
	}


	return bonus;
}

Evaluation ChessBoard::staticEvaluation()
{
	// Detect mate
	if(toMove == WHITE)
		if(isWhiteMate())
			return Evaluation(0, 0, BLACK_WINS);
	if(toMove == BLACK)
		if(isBlackMate())
			return Evaluation(0, 0, WHITE_WINS);

	double evaluation = 0;
	evaluation += basicMaterialCount();
	evaluation += positionBonusses();
	//evaluation += pawnStructureBonus();
	evaluation += 1 * rand() / RAND_MAX;


	return Evaluation(evaluation);
}

Evaluation ChessBoard::dynamicEvaluation(int searchDepth, int * nodeCount, std::vector<Move> &pv)
{
	return dynamicEvaluationWrapper(searchDepth, nodeCount, Evaluation(0, 0, BLACK_WINS), Evaluation(0, 0, WHITE_WINS), pv);
}

Evaluation ChessBoard::dynamicEvaluationWrapper(int searchDepth, int * nodeCount, Evaluation alpha, Evaluation beta, std::vector<Move> &pv)
{
	(*nodeCount)++;

	if(searchDepth <= 1 )
		return quiscenceSearch(nodeCount, alpha, beta, pv, false);

	std::vector<Move> moves = legalMoves();
	if (moves.empty())
	{
		pv.clear();
		if(toMove == WHITE)
		{
			if(isWhiteKingUnderAttack())
			{
				return Evaluation(0, 0, BLACK_WINS);
			}
			else
			{
				return Evaluation(0);
			}
		}
		else
		{
			if(isBlackKingUnderAttack())
			{
				return Evaluation(0, 0, WHITE_WINS);
			}
			else
			{
				return Evaluation(0);
			}
		}
	}

	orderMoves(moves);

	Evaluation currentBest;
	if(toMove == WHITE)
		currentBest = alpha;
	else
		currentBest = beta;

	int currentBestMove = 0;
	std::vector<Move> currentBestPV;
	for(int i = 0; i < (int) moves.size(); i++)
	{
		ChessBoard tempBoard(*this);
		assert((int)moves.size() > i);
		tempBoard.performMove(moves.at(i));
		std::vector<Move> tempPv;
		Evaluation eval = tempBoard.dynamicEvaluationWrapper(searchDepth - 1, nodeCount, alpha, beta, tempPv);
		if(toMove == WHITE)
		{
			if(eval > currentBest)
			{
				currentBestPV.clear();
				currentBestPV.push_back(moves.at(i));
				currentBestPV.insert(currentBestPV.end(), tempPv.begin(), tempPv.end());
				currentBest = eval;
				currentBestMove = i;
				if(eval > alpha)
				{
					alpha = eval;
				}
				if(!(alpha < beta))
				{
					break;
				}
			}
		}
		else
		{
			if(eval < currentBest)
			{
				currentBestPV.clear();
				currentBestPV.push_back(moves.at(i));
				currentBestPV.insert(currentBestPV.end(), tempPv.begin(), tempPv.end());
				currentBest = eval;
				currentBestMove = i;
				if(eval < beta)
				{
					beta = eval;
				}
				if(!(alpha < beta))
				{
					break;
				}
			}
		}
	}

	pv = currentBestPV;
	bestMove = moves.at(currentBestMove);
	// Trouble with mate scoring
	currentBest.increaseMovesToMateByOne();
	return currentBest;
}


Evaluation ChessBoard::quiscenceSearch(int * nodeCount, Evaluation alpha, Evaluation beta, std::vector<Move> &pv, bool final)
{
	(*nodeCount)++;

	std::vector<Move> moves = legalMoves();
	if (moves.empty())
	{
		pv.clear();
		if(toMove == WHITE)
		{
			if(isWhiteKingUnderAttack())
			{
				return Evaluation(0, 0, BLACK_WINS);
			}
			else
			{
				return Evaluation(0);
			}
		}
		else
		{
			if(isBlackKingUnderAttack())
			{
				return Evaluation(0, 0, WHITE_WINS);
			}
			else
			{
				return Evaluation(0);
			}
		}
	}

	orderMoves(moves);
	::std::reverse(moves.begin(), moves.end());

	Evaluation currentBest;
	if(toMove == WHITE)
		currentBest = alpha;
	else
		currentBest = beta;

	int currentBestMove = 0;
	std::vector<Move> currentBestPV;
	for(int i = 0; i < (int) moves.size(); i++)
	{
		ChessBoard tempBoard(*this);
		assert((int) moves.size() > i);
		std::vector<Move> tempPv;
		Evaluation eval;
		if(tempBoard.get(moves.at(i).to.column, moves.at(i).to.row) != NO_PIECE && !final)
		{
			tempBoard.performMove(moves.at(i));
			eval = tempBoard.quiscenceSearch(nodeCount, alpha, beta, tempPv, false);
		}
		else
		{
			tempBoard.performMove(moves.at(i));
			eval = tempBoard.staticEvaluation();
		}
		if(toMove == WHITE)
		{
			if(eval > currentBest)
			{
				currentBestPV.clear();
				currentBestPV.push_back(moves.at(i));
				currentBestPV.insert(currentBestPV.end(), tempPv.begin(), tempPv.end());
				currentBest = eval;
				currentBestMove = i;
				if(eval > alpha)
				{
					alpha = eval;
				}
				if(!(alpha < beta))
				{
					break;
				}
			}
		}
		else
		{
			if(eval < currentBest)
			{
				currentBestPV.clear();
				currentBestPV.push_back(moves.at(i));
				currentBestPV.insert(currentBestPV.end(), tempPv.begin(), tempPv.end());
				currentBest = eval;
				currentBestMove = i;
				if(eval < beta)
				{
					beta = eval;
				}
				if(!(alpha < beta))
				{
					break;
				}
			}
		}
	}

	pv = currentBestPV;
	bestMove = moves.at(currentBestMove);
	// Trouble with mate scoring
	currentBest.increaseMovesToMateByOne();
	return currentBest;
}



void ChessBoard::performBestMove()
{
	performMove(bestMove);
}

void ChessBoard::setupBoardFromFen(char* inputString)
{
	// rnbqkbnr/pppppppp/8/8/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1
	
	int row = 7;
	int column = 0;

	int index = 0;
	bool moreToCome = true;
	while(moreToCome)
	{
		char t = inputString[index];
		if(t == 'r'){
			board[column][row] = BLACK_ROOK;
			column++;}
		else if(t == 'n'){
			board[column][row] = BLACK_KNIGHT;
			column++;}
		else if(t == 'b'){
			board[column][row] = BLACK_BISHOP;
			column++;}
		else if(t == 'q'){
			board[column][row] = BLACK_QUEEN;
			column++;}
		else if(t == 'k'){
			board[column][row] = BLACK_KING;
			column++;}
		else if(t == 'p'){
			board[column][row] = BLACK_PAWN;
			column++;}
		else if(t == 'R'){
			board[column][row] = WHITE_ROOK;
			column++;}
		else if(t == 'N'){
			board[column][row] = WHITE_KNIGHT;
			column++;}
		else if(t == 'B'){
			board[column][row] = WHITE_BISHOP;
			column++;}
		else if(t == 'Q'){
			board[column][row] = WHITE_QUEEN;
			column++;}
		else if(t == 'K'){
			board[column][row] = WHITE_KING;
			column++;}
		else if(t == 'P'){
			board[column][row] = WHITE_PAWN;
			column++;}
		else if(t == '/'){
			row--;
			column = 0;}
		else if('0' < t && t < '9') {
			for(int i = 0; i < t - '0'; i++)
			{
				board[column][row] = NO_PIECE;
				column++;
			}
		}
		else 
			moreToCome = false;
		index++;
	}

	// Read side to move
	char t = inputString[index];
	if(t == 'w')
	{
		toMove = WHITE;
	}
	else
	{
		assert(t == 'b');
		toMove = BLACK;
	}

	// Read castling rights
	index += 2;
	t = inputString[index];
	whiteCastleKing = false;
	whiteCastleQueen = false;
	blackCastleKing = false;
	blackCastleQueen = false;
	while(t != ' ')
	{
		if(t == 'K')
			whiteCastleKing = true;
		if(t == 'k')
			blackCastleKing = true;
		if(t == 'Q')
			whiteCastleQueen = true;
		if(t == 'q')
			blackCastleQueen = true;
		index++;
		t = inputString[index];
	}

	// Read en pessant square
}


void ChessBoard::whiteCastling( std::vector<Move> &moves )
{
	if(whiteCastleKing == true)
	{
		if(isWhiteKingUnderAttack())
		{
			return;
		}
		if(get(Position(5, 0)) == NO_PIECE 
			&& isLocationAttackedByBlackPieces(Position(5, 0)) == false 
			&& get(Position(6, 0)) == NO_PIECE
			&& isLocationAttackedByBlackPieces(Position(6, 0)) == false)
		{
			moves.push_back(Move(Position(4, 0), Position(6, 0), CASTLE_KING));
		}
	}
	if(whiteCastleQueen == true)
	{
		if(isWhiteKingUnderAttack())
		{
			return;
		}
		if(get(Position(3, 0)) == NO_PIECE 
			&& isLocationAttackedByBlackPieces(Position(3, 0)) == false 
			&& get(Position(2, 0)) == NO_PIECE
			&& isLocationAttackedByBlackPieces(Position(2, 0)) == false)
		{
			moves.push_back(Move(Position(4, 0), Position(2, 0), CASTLE_QUEEN));
		}
	}
}

void ChessBoard::blackCastling( std::vector<Move> &moves )
{
	if(blackCastleKing == true)
	{
		if(isBlackKingUnderAttack())
		{
			return;
		}
		if(get(Position(5, 7)) == NO_PIECE 
			&& get(Position(6, 7)) == NO_PIECE
			&& isLocationAttackedByWhitePieces(Position(5, 7)) == false 
			&& isLocationAttackedByWhitePieces(Position(6, 7)) == false)
		{
			moves.push_back(Move(Position(4, 7), Position(6, 7), CASTLE_KING));
		}
	}
	if(blackCastleQueen == true)
	{
		if(isBlackKingUnderAttack())
		{
			return;
		}
		if(get(Position(3, 7)) == NO_PIECE 
			&& get(Position(2, 7)) == NO_PIECE
			&& isLocationAttackedByWhitePieces(Position(3, 7)) == false 
			&& isLocationAttackedByWhitePieces(Position(2, 7)) == false)
		{
			moves.push_back(Move(Position(4, 7), Position(2, 7), CASTLE_QUEEN));
		}
	}
}

void ChessBoard::orderMoves( std::vector<Move> &moves )
{
	// Order moves such that captures are located first

	std::vector<Move> captures;
	std::vector<Move> nonCaptures;

	for(int i = 0; i < (int) moves.size(); i++)
	{
		Move mov = moves.at(i);
		if(board[mov.to.column][mov.to.row] != NO_PIECE)
			captures.push_back(mov);
		else
			nonCaptures.push_back(mov);
	}

	moves.clear();
	moves.insert(moves.end(), captures.begin(), captures.end());
	moves.insert(moves.end(), nonCaptures.begin(), nonCaptures.end());
}

void ChessBoard::takeBackLastMove()
{
	Move undoMove = history.back();
	history.pop_back();

	bool castelingDetected = false;

	// Detect casteling
	if(undoMove.from.column == 4)
	{
		if(undoMove.to.column == 6)
		{
			if(undoMove.from.row == 0 && board[6][0] == WHITE_KING)
			{
				castelingDetected = true;

				// White O-O
				board[4][0] = WHITE_KING;
				board[5][0] = NO_PIECE;
				board[6][0] = NO_PIECE;
				board[7][0] = WHITE_ROOK;
			}
			if(undoMove.from.row == 7 && board[6][7] == BLACK_KING)
			{
				castelingDetected = true;

				// Black O-O
				board[4][7] = BLACK_KING;
				board[5][7] = NO_PIECE;
				board[6][7] = NO_PIECE;
				board[7][7] = BLACK_ROOK;
			}
		}
		if(undoMove.to.column == 2)
		{
			if(undoMove.from.row == 0 && board[2][0] == WHITE_KING)
			{
				castelingDetected = true;

				// White O-O-O
				board[4][0] = WHITE_KING;
				board[3][0] = NO_PIECE;
				board[2][0] = NO_PIECE;
				board[1][0] = NO_PIECE;
				board[0][0] = WHITE_ROOK;
			}
			if(undoMove.from.row == 7 && board[2][7] == BLACK_KING)
			{
				castelingDetected = true;

				// White O-O-O
				board[4][7] = BLACK_KING;
				board[3][7] = NO_PIECE;
				board[2][7] = NO_PIECE;
				board[1][7] = NO_PIECE;
				board[0][7] = BLACK_ROOK;
			}
		}
	}

	if(castelingDetected == false)
	{
		board[undoMove.from.column][undoMove.from.row] = board[undoMove.to.column][undoMove.to.row];
		board[undoMove.to.column][undoMove.to.row] = captures.back();
	}
	captures.pop_back();
	if(toMove == WHITE)
		toMove = BLACK;
	else
		toMove = WHITE;
}