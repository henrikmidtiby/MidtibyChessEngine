#ifndef EVALUATION_H
#define EVALUATION_H
#include <math.h>
#include <assert.h>

enum Side {WHITE, BLACK};
enum EvaluationState {BLACK_WINS, NO_MATE, WHITE_WINS};

class Evaluation {
private:
	double boardEvaluation;
	int mateIn;
	EvaluationState mateState;
public:
	Evaluation()
	{
		boardEvaluation = 0;
		mateIn = 0;
		mateState = NO_MATE;
	}
	Evaluation(double eval)
	{
		boardEvaluation = eval;
		mateIn = 0;
		mateState = NO_MATE;
	}
	Evaluation(double eval, int mateInHalfMoves, EvaluationState sideToWin)
	{
		boardEvaluation = eval;
		mateIn = mateInHalfMoves;
		mateState = sideToWin;
	}
	bool operator!=(Evaluation val)
	{
		return !(*this == val);
	}
	bool operator==(Evaluation val)
	{
		if(mateState != val.mateState)
			return false;
		if(mateState != NO_MATE)
			if(mateIn == val.mateIn)
				return true;
			else
				return false;
		else
			if(fabs(boardEvaluation - val.boardEvaluation) < 0.0001)
				return true;
			else
				return false;
	}
	bool operator>(Evaluation val)
	{
		if(mateState != val.mateState)
		{
			if(mateState == WHITE_WINS || val.mateState == BLACK_WINS)
				return true;
			if(mateState == BLACK_WINS || val.mateState == WHITE_WINS)
				return false;
		}
		if(mateState == BLACK_WINS)
		{
			return mateIn > val.mateIn;
		}
		if(mateState == WHITE_WINS)
		{
			return mateIn < val.mateIn;
		}

		return false;
	}
};

#endif
