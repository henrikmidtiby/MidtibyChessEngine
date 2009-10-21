enum Pieces {NO_PIECE, WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_PAWN, BLACK_PAWN, BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING};
enum Side {WHITE, BLACK};

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
};