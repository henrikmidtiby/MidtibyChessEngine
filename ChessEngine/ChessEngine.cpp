// ChessEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "UnitTest++.h"
#include "tests.h"
#include "chessboard.h"
#include <iostream>
#include <ctime>

bool recognizeAsMove( char* buffer, Move* mov ) 
{
	// Handle standard moves
	if(strlen(buffer) == 4 
		&& 'a' <= (int) buffer[0] && (int) buffer[0] <= 'h'
		&& '1' <= (int) buffer[1] && (int) buffer[1] <= '8'
		&& 'a' <= (int) buffer[2] && (int) buffer[2] <= 'h'
		&& '1' <= (int) buffer[3] && (int) buffer[3] <= '8')
	{
		*mov = Move(Position(buffer[0] - 'a', buffer[1] - '1'), 
			Position(buffer[2] - 'a', buffer[3] - '1'));
		return true;
	}

	// Handle promotion moves
	if(strlen(buffer) == 5 
		&& 'a' <= (int) buffer[0] && (int) buffer[0] <= 'h'
		&& '1' <= (int) buffer[1] && (int) buffer[1] <= '8'
		&& 'a' <= (int) buffer[2] && (int) buffer[2] <= 'h'
		&& '1' <= (int) buffer[3] && (int) buffer[3] <= '8')
	{
		Position pos1(buffer[0] - 'a', buffer[1] - '1');
		Position pos2(buffer[2] - 'a', buffer[3] - '1');

		if(buffer[4] == 'q')
		{
			*mov = Move(pos1, pos2, PROMOTE_TO_QUEEN);
			return true;
		}
		if(buffer[4] == 'r')
		{
			*mov = Move(pos1, pos2, PROMOTE_TO_ROOK);
			return true;
		}
		if(buffer[4] == 'n')
		{
			*mov = Move(pos1, pos2, PROMOTE_TO_KNIGHT);
			return true;
		}
		if(buffer[4] == 'b')
		{
			*mov = Move(pos1, pos2, PROMOTE_TO_BISHOP);
			return true;
		}
		return false;
	}

	return false;
}

void echoToGuiAndFile(FILE** fh, char* buffer)
{
	fprintf_s(*fh, "eng: %s", buffer);
	printf("%s", buffer);
}


int uciInterface()
{
	FILE* fileHandle;
	fopen_s(&fileHandle, "inputFromGui.txt", "w");

	ChessBoard board;
	board.initializeGame();
	std::vector<Move> moves;

	Move mov(Position(0, 0), Position(0, 0));

	while(true)
	{
		// Get command from command line
		char buffer[10000];
		std::cin.getline(buffer,10000);


		fprintf_s(fileHandle, "gui: %s\n", buffer);
		// Handle commands
		if(strcmp(buffer, "uci") == 0)
		{
			echoToGuiAndFile(&fileHandle, "id name hsmChess\n");
			echoToGuiAndFile(&fileHandle, "id author Henrik Skov Midtiby\n");
			echoToGuiAndFile(&fileHandle, "uciok\n");
			continue;
		}
		if(strcmp(buffer, "isready") == 0)
		{
			echoToGuiAndFile(&fileHandle, "readyok\n");
			continue;
		}
		if(strncmp(buffer, "position", 8) == 0)
		{
			if(strncmp(&buffer[9], "startpos", 8) == 0)
			{
				board.initializeGame();
				int index = strlen("position startpos moves ");
				while(index < (int) strlen(buffer))
				{
//					fprintf_s(fileHandle, "info \"%s\"\n", &buffer[index]);
					char tempBuffer[6];
					// Locate the next " "
					int length = strcspn(&buffer[index], " ");	
//					fprintf_s(fileHandle, "info \"length %d\"\n", length);
					assert(length < 6);
					for(int i = 0; i < length; i++)
					{
						tempBuffer[i] = buffer[index + i];
					}
					tempBuffer[length] = '\0';
					strncpy_s(&buffer[index], 10000-index, tempBuffer, length);
//					fprintf_s(fileHandle, "info \"string: \'%c%c%c%c\'\"\n", tempBuffer[0], tempBuffer[1], tempBuffer[2], tempBuffer[3]);
					if(recognizeAsMove(tempBuffer, &mov))
					{
						//fprintf_s(fileHandle, "info \"%s\"\n", mov.toString().c_str());

						moves.push_back(mov);
						board.performMove(mov);
					}
					index += length + 1;
				}
			}
			continue;
		}
		if(strcmp(buffer, "quit") == 0)
		{
			return 0;
		}
		if(strncmp(buffer, "go", 2) == 0)
		{
			int whiteTime = 0;
			int blackTime = 0;
			int whiteTimeInc = 0;
			int blackTimeInc = 0;
			sscanf(buffer, "go wtime %d btime %d winc %d binc %d", &whiteTime, &blackTime, &whiteTimeInc, &blackTimeInc);
			int timeToUse;
			if(board.sideToMove() == WHITE)
			{
				timeToUse = whiteTime / 40;
			}
			else
			{
				timeToUse = blackTime / 40;
			}


			clock_t initialTime = clock();
			int maxDepth = 5;
			int nodeCount = 0;
			char temp[1000];
			std::vector<Move> pv;
			for(int depth = 0; depth < 1000; depth++)
			{
				Evaluation eval = board.dynamicEvaluation(depth, &nodeCount, pv);
				std::string pvString = "";
				for(int i = 0; i < (int) pv.size(); i++)
				{
					pvString = pvString + pv.at(i).toString() + " ";
				}
				int usedTime = (int) (1000. * (clock() - initialTime)) / CLOCKS_PER_SEC;
				int nodesPrSec = (int) (1000.0 * nodeCount) / (usedTime + 1);
				sprintf_s(temp, 1000, "info depth %d nps %d\n", depth, nodesPrSec);
				echoToGuiAndFile(&fileHandle, temp);
				sprintf_s(temp, 100, "uciok\n");
				echoToGuiAndFile(&fileHandle, temp);

				if(board.sideToMove() == WHITE)
					sprintf_s(temp, 1000, "info depth %d score cp %d time %d nodes %d nps %d pv %s\r\n", depth, (int) (eval.getBoardEvaluation()), usedTime, nodeCount, nodesPrSec, pvString.c_str());
				else
					sprintf_s(temp, 1000, "info depth %d score cp %d time %d nodes %d nps %d pv %s\r\n", depth, (int) (-eval.getBoardEvaluation()), usedTime, nodeCount, nodesPrSec, pvString.c_str());
				echoToGuiAndFile(&fileHandle, temp);
				fflush(stdout);

				if(2*usedTime > timeToUse)
				{
					break;
				}
			}

			sprintf_s(temp, 100, "bestmove %s\n", board.bestMove.toString().c_str());
			fflush(stdout);
			echoToGuiAndFile(&fileHandle, temp);
			board.performBestMove();
			moves.push_back(board.bestMove);

			continue;
		}

		// Command not recognized, it may be a move ...
		printf("command not recognized: %s\n", buffer);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	srand(time(0));

	// Only perform unit tests if one additional argument is given
	if(argc == 2)
	{
		if(strcmp(argv[1], "unittest") == 0)
		{
			return UnitTest::RunAllTests();
		}

		if(strcmp(argv[1], "xboard") == 0)
		{
			return uciInterface();
		}
	}

	return uciInterface();

	return 0;
}

TEST ( RecognizeMoves )
{
	Move mov(Position(0, 0), Position(0, 0));
	// Normal moves
	CHECK(recognizeAsMove("e2e4", &mov));
	CHECK(mov == Move(Position(4, 1), Position(4, 3)));
	CHECK(!recognizeAsMove("e2", &mov));

	// Promotion
	CHECK(recognizeAsMove("e7e8q", &mov));
	CHECK(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_QUEEN));
	CHECK(recognizeAsMove("e7e8r", &mov));
	CHECK(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_ROOK));
	CHECK(recognizeAsMove("e7e8n", &mov));
	CHECK(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_KNIGHT));
	CHECK(recognizeAsMove("e7e8b", &mov));
	CHECK(mov == Move(Position(4, 6), Position(4, 7), PROMOTE_TO_BISHOP));

}