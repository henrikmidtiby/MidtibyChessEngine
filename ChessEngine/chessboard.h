#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <utility>
#include <vector>
#include <string>

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
	Position() {column = 0; row = 0;}
	Position(int c, int r) {column = c; row = r;};
	bool isEqualTo(Position b) {return (column == b.column) && (row == b.row);};
};

class Move
{
public:
	Position from;
	Position to;
	Move(int cf, int rf, int ct, int rt) {from.column = cf; from.row = rf; to.column = ct; to.row = rt;};
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
	void performMove(Move mov);
	void performMove(Position pos0, Position pos1);
	bool isWhiteKingUnderAttack();
	bool isBlackKingUnderAttack();
	void clearBoard();
	void placePiece(Position pos, Pieces piece);
	void setSideToMove(Side side);
	Pieces firstPieceInDirection(Position pos, int dirColumn, int dirRow);
	Position locateWhiteKing();
	Position locateBlackKing();
	bool isLocationAttackedByBlackPieces(Position pos);
	bool isLocationAttackedByWhitePieces(Position pos);
	std::vector<Move> legalMoves();
	std::vector<Move> PossibleMoves();
	std::vector<Move> PossibleWhiteMoves();
	std::vector<Move> PossibleBlackMoves();

	void moveLikeWhiteKing( int column, int row, std::vector<Move> &moves );
	void moveLikeWhitePawn( int column, int row, std::vector<Move> &moves );
	void moveLikeWhiteBishop( int column, int row, std::vector<Move> &moves );
	void moveLikeWhiteKnight( int column, int row, std::vector<Move> &moves );
	void moveLikeWhiteRook( int column, int row, std::vector<Move> &moves );
	void moveLikeBlackKnight( int column, int row, std::vector<Move> &moves );
	void moveLikeBlackPawn( int column, int row, std::vector<Move> &moves );
	void moveLikeBlackKing( int column, int row, std::vector<Move> &moves );
	void moveLikeBlackBishop( int column, int row, std::vector<Move> &moves );
	void moveLikeBlackRook( int column, int row, std::vector<Move> &moves );
	bool isBlackPiece(Pieces piece);
	bool isWhitePiece(Pieces piece);
	bool isWhiteOrEmpty(Pieces piece);
	bool isBlackOrEmpty(Pieces piece);
	bool isOutsideBoard(Position pos);
	void moveWhitePieceInLine( int column, int row, int dcolumn, int drow, std::vector<Move> &moves );
	void moveBlackPieceInLine( int column, int row, int dcolumn, int drow, std::vector<Move> &moves );

	char encodePiece(Pieces piece);
	void printBoard();
	void printMovesFromList(std::vector<Move> moves);
};


#endif
