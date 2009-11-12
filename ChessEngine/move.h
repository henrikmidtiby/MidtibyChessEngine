#ifndef MOVE_H
#define MOVE_H
#include "position.h"

enum MoveSpecial {STANDARD_MOVE, CASTLE_QUEEN, 
CASTLE_KING, PROMOTE_TO_QUEEN, PROMOTE_TO_ROOK, 
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
		if(notice == CASTLE_KING)
		{
//			return std::string("O-O");
		}
		if(notice == CASTLE_QUEEN)
		{
//			return std::string("O-O-O");
		}
		std::string res;
		res.append(from.toString());
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
	bool operator==(Move mov)
	{
		if(from.column != mov.from.column)
			return false;
		if(from.row!= mov.from.row)
			return false;
		if(to.column != mov.to.column)
			return false;
		if(to.row != mov.to.row)
			return false;
		if(notice != mov.notice)
			return false;
		return true;
	}
};

#endif