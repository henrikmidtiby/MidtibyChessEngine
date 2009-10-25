#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <utility>

enum Pieces {NO_PIECE, OUTSIDE_BOARD,
	WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, 
	WHITE_QUEEN, WHITE_KING, WHITE_PAWN, 
	BLACK_PAWN, BLACK_ROOK, BLACK_KNIGHT, 
	BLACK_BISHOP, BLACK_QUEEN, BLACK_KING};
enum Side {WHITE, BLACK};

class Position
{
public:
	int column;
	int row;
	Position(int c, int r) {column = c; row = r;};
	bool isEqualTo(Position b) {return (column == b.column) && (row == b.row);};
};

class ChessBoard {
private:
	Pieces board[8][8];
	Side toMove;

public:
	ChessBoard();
	void initializeGame();
	Pieces get(int column, int row);
	Side sideToMove();
	void performMove(int column0, int row0, int column1, int row1);
	bool isWhiteKingUnderAttack();
	bool isBlackKingUnderAttack();
	void clearBoard();
	void placePiece(Position pos, Pieces piece);
	void setSideToMove(Side side);
	Pieces firstPieceInDirection(int colum, int row, int dirColumn, int dirRow);
	Position locateWhiteKing();
	Position locateBlackKing();
	bool isLocationAttackedByBlackPieces(Position pos);
	bool isLocationAttackedByWhitePieces(Position pos);
};

#endif
