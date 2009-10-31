#include "stdafx.h"
#include "chessboard.h"
#include <assert.h>
#include <string>

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

void ChessBoard::performMove(Move mov)
{
	if(mov.notice == STANDARD_MOVE)
	{
		board[mov.to.column][mov.to.row] = board[mov.from.column][mov.from.row];
		board[mov.from.column][mov.from.row] = NO_PIECE;
	}
	else if(mov.notice == PROMOTE_TO_QUEEN)
	{
		if(toMove == WHITE)
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
		if(toMove == WHITE)
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
		if(toMove == WHITE)
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
		if(toMove == WHITE)
		{
			board[mov.to.column][mov.to.row] = WHITE_BISHOP;
		}
		else
		{
			board[mov.to.column][mov.to.row] = BLACK_BISHOP;
		}
		board[mov.from.column][mov.from.row] = NO_PIECE;
	}

	if(toMove == WHITE)
	{
		toMove = BLACK;
	}
	else
	{
		toMove = WHITE;
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

void ChessBoard::promotePawnMove(Position from, Position to, std::vector<Move> &moves)
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
		if(isBlackPiece(board[column - 1][row + 1]))
		{
			promotePawnMove(Position(column, row), Position(column - 1, row + 1), moves);
		}
		if(isBlackPiece(board[column + 1][row + 1]))
		{
			promotePawnMove(Position(column, row), Position(column + 1, row + 1), moves);
		}
	}
	else
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
}

void ChessBoard::moveLikeWhiteKing( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isBlackOrEmpty(get(column + kingMovesColumn[i], row + kingMovesRow[i])))
			moves.push_back(Move(column, row, column + kingMovesColumn[i], row + kingMovesRow[i]));
	}
}

void ChessBoard::moveLikeWhiteKnight( int column, int row, std::vector<Move> &moves )
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

void ChessBoard::moveLikeBlackKnight( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isWhiteOrEmpty(get(column + knightMovesColumn[i], row + knightMovesRow[i])))
			moves.push_back(Move(column, row, column + knightMovesColumn[i], row + knightMovesRow[i]));
	}
}

void ChessBoard::moveLikeBlackPawn( int column, int row, std::vector<Move> &moves )
{
	if(row == 1)
	{
		if(board[column][row - 1] == NO_PIECE)
			promotePawnMove(Position(column, row), Position(column, row - 1), moves);
		if(isWhitePiece(board[column - 1][row - 1]))
			promotePawnMove(Position(column, row), Position(column - 1, row - 1), moves);
		if(isWhitePiece(board[column + 1][row - 1]))
			promotePawnMove(Position(column, row), Position(column + 1, row - 1), moves);
	}
	else
	{
		if(board[column][row - 1] == NO_PIECE)
		{
			moves.push_back(Move(column, row, column, row - 1));
			if(row == 6 && board[column][row - 2] == NO_PIECE)
				moves.push_back(Move(column, row, column, row - 2));
		}
		if(isWhitePiece(board[column - 1][row - 1]))
			moves.push_back(Move(column, row, column - 1, row - 1));
		if(isWhitePiece(board[column + 1][row - 1]))
			moves.push_back(Move(column, row, column + 1, row - 1));
	}
}

void ChessBoard::moveLikeBlackKing( int column, int row, std::vector<Move> &moves )
{
	for(int i = 0; i < 8; i++)
	{
		if(isWhiteOrEmpty(get(column + kingMovesColumn[i], row + kingMovesRow[i])))
			moves.push_back(Move(column, row, column + kingMovesColumn[i], row + kingMovesRow[i]));
	}
}

void ChessBoard::moveBlackPieceInLine( int column, int row, int dcolumn, int drow, std::vector<Move> &moves )
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

void ChessBoard::moveLikeBlackRook( int column, int row, std::vector<Move> &moves )
{
	moveBlackPieceInLine(column, row,  0,  1, moves);
	moveBlackPieceInLine(column, row,  0, -1, moves);
	moveBlackPieceInLine(column, row,  1,  0, moves);
	moveBlackPieceInLine(column, row, -1,  0, moves);
}

void ChessBoard::moveLikeBlackBishop( int column, int row, std::vector<Move> &moves )
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
		return 'K';
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
		return 'k';
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
	if(piece == WHITE_KING) return  100;
	if(piece == BLACK_KING) return -100;
	if(piece == WHITE_QUEEN) return  9;
	if(piece == BLACK_QUEEN) return -9;
	if(piece == WHITE_ROOK) return  5;
	if(piece == BLACK_ROOK) return -5;
	if(piece == WHITE_KNIGHT) return  3;
	if(piece == BLACK_KNIGHT) return -3;
	if(piece == WHITE_BISHOP) return  3;
	if(piece == BLACK_BISHOP) return -3;
	if(piece == WHITE_PAWN) return  1;
	if(piece == BLACK_PAWN) return -1;
	return 0;
}

double ChessBoard::basicMaterialCount()
{
	double material = 0;
	for(int column = 0; column < 8; column++)
		for(int row = 0; row < 8; row++)
			material += pieceValue(get(column, row));
	return material;
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

	return Evaluation(evaluation);
}