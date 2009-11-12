#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <utility>
#include <vector>
#include <string>
#include "position.h"
#include "move.h"
#include "evaluation.h"

enum Pieces {NO_PIECE, OUTSIDE_BOARD,
	WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, 
	WHITE_QUEEN, WHITE_KING, WHITE_PAWN, 
	BLACK_PAWN, BLACK_ROOK, BLACK_KNIGHT, 
	BLACK_BISHOP, BLACK_QUEEN, BLACK_KING};



class ChessBoard {
private:
	Pieces board[8][8];
	Side toMove;

public:
	int bestMove;
	bool whiteCastleKing;
	bool whiteCastleQueen;
	bool blackCastleKing;
	bool blackCastleQueen;

	ChessBoard();
	void initializeGame();
	Pieces get(int column, int row);
	Pieces get(Position pos);
	Side sideToMove();
	void performMove(Move mov);
	void performMove(Position pos0, Position pos1);
	void performMoveWrapper(Move mov);
	void clearBoard();
	void placePiece(Position pos, Pieces piece);
	void setSideToMove(Side side);
	std::vector<Move> legalMoves();
	std::vector<Move> possibleMoves();
	void printBoard();
	void printMovesFromList(std::vector<Move> moves);
	void performBestMove();
	void setupBoardFromFen(char * inputString);



	bool isBlackMate();
	bool isWhiteMate();
	bool isThereLegalMovesAvailable();
	bool isWhiteKingUnderAttack();
	bool isBlackKingUnderAttack();
	Pieces firstPieceInDirection(Position pos, int dirColumn, int dirRow);
	Position locateWhiteKing();
	Position locateBlackKing();
	bool isLocationAttackedByBlackPieces(Position pos);
	bool isLocationAttackedByWhitePieces(Position pos);
	std::vector<Move> possibleWhiteMoves();
	std::vector<Move> possibleBlackMoves();
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
	void promotePawnMove(Position from, Position to, std::vector<Move> &moves);
	char encodePiece(Pieces piece);
	Evaluation staticEvaluation();
	double pieceValue(Pieces piece);
	double basicMaterialCount();
	Evaluation dynamicEvaluation(int searchDepth, int * nodeCount);
	void whiteCastling( std::vector<Move> &moves );
	void blackCastling( std::vector<Move> &moves );
};


#endif
