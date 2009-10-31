#ifndef MOVE_H
#define MOVE_H
#include "position.h"

enum MoveSpecial {STANDARD_MOVE, CASTLE_LONG, 
CASTLE_SHORT, PROMOTE_TO_QUEEN, PROMOTE_TO_ROOK, 
PROMOTE_TO_KNIGHT, PROMOTE_TO_BISHOP};


class Move
{
public:
	Position from;
	Position to;
	MoveSpecial notice;
	Move(Position fromPos, Position toPos) {from = fromPos; to = toPos; notice = STANDARD_MOVE;};
	Move(Position fromPos, Position toPos, MoveSpecial note) {from = fromPos; to = toPos; notice = note;};
	Move(int cf, int rf, int ct, int rt) 
	{
		from.column = cf; from.row = rf; to.column = ct; to.row = rt; notice = STANDARD_MOVE;
	};
	Move(int cf, int rf, int ct, int rt, MoveSpecial note) 
	{
		from.column = cf; 
		from.row = rf; 
		to.column = ct; 
		to.row = rt;
		notice = note;
	};
	std::string toString()
	{
		if(notice == CASTLE_SHORT)
		{
			return std::string("O-O");
		}
		if(notice == CASTLE_LONG)
		{
			return std::string("O-O-O");
		}
		std::string res;
		res.append(from.toString());
		res.append(1, '-');
		res.append(to.toString());
		if(notice == PROMOTE_TO_QUEEN)
		{
			res.append(1, 'Q');
		}
		if(notice == PROMOTE_TO_ROOK)
		{
			res.append(1, 'R');
		}
		if(notice == PROMOTE_TO_BISHOP)
		{
			res.append(1, 'B');
		}
		if(notice == PROMOTE_TO_KNIGHT)
		{
			res.append(1, 'N');
		}
		return res;
	}
};

#endif