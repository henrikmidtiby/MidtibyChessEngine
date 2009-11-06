#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
	int column;
	int row;
	Position() {column = 0; row = 0;}
	Position(int c, int r) {column = c; row = r;};
	bool isEqualTo(Position b) 
	{
		return (column == b.column) && (row == b.row);
	};
	std::string toString()
	{
		std::string res;
		res.append(1, 'a' + column);
		res.append(1, '1' + row);
		return res;
	};
	bool operator==(Position pos)
	{
		if(column != pos.column)
			return false;
		if(row != pos.row)
			return false;
		return true;
	}
};

#endif