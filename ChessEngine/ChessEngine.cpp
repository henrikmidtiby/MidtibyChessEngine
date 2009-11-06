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


int xboardInterface()
{
	FILE* fileHandle;
	fopen_s(&fileHandle, "inputFromGui.txt", "w");

	ChessBoard board;
	board.initializeGame();
	std::vector<Move> moves;

	Move mov(Position(0, 0), Position(0, 0));

	while(true)
	{
		// Get command from commandline
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
				while(index < strlen(buffer))
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
					strncpy(&buffer[index], tempBuffer, length);
//					fprintf_s(fileHandle, "info \"string: \'%c%c%c%c\'\"\n", tempBuffer[0], tempBuffer[1], tempBuffer[2], tempBuffer[3]);
					if(recognizeAsMove(tempBuffer, &mov))
					{
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
		if(strcmp(buffer, "new") == 0)
		{
			board.initializeGame();
			continue;
		}
		if(strcmp(buffer, "print") == 0)
		{
			board.printBoard();
			continue;
		}
		if(strcmp(buffer, "undo") == 0)
		{
			moves.pop_back();
			board.initializeGame();
			for(int i = 0; i < moves.size(); i++)
			{
				board.performMove(moves.at(i));
			}
			continue;
		}
		if(strncmp(buffer, "go", 2) == 0)
		{
			std::vector<Move> currentMoves = board.legalMoves();
			Evaluation eval = board.dynamicEvaluation(3);
			//printf("Performing move: %s (%s)\n\n", currentMoves.at(board.bestMove).toString().c_str(), eval.toString().c_str());
			char temp[100];
			sprintf_s(temp, 100, "info depth 4\n");
			echoToGuiAndFile(&fileHandle, temp);
			sprintf_s(temp, 100, "info score cp %d\n", (int) (100*eval.getBoardEvaluation()));
			echoToGuiAndFile(&fileHandle, temp);
			sprintf_s(temp, 100, "bestmove %s\n", currentMoves.at(board.bestMove).toString().c_str());
			echoToGuiAndFile(&fileHandle, temp);
			board.performBestMove();
			moves.push_back(currentMoves.at(board.bestMove));

			continue;
		}
		if(recognizeAsMove(buffer, &mov))
		{
			//printf("Move recognized: %s\n", mov.toString().c_str());
			moves.push_back(mov);
			board.performMove(mov);

			std::vector<Move> currentMoves = board.legalMoves();
			Evaluation eval = board.dynamicEvaluation(2);
			//printf("Performing move: %s (%s)\n\n", currentMoves.at(board.bestMove).toString().c_str(), eval.toString().c_str());
			printf("move %s\n", currentMoves.at(board.bestMove).toString().c_str());
			board.performBestMove();
			moves.push_back(currentMoves.at(board.bestMove));

			continue;
		}

		// Command not recognized, it may be a move ...
		std::cout << buffer << std::endl;

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
			return xboardInterface();
		}
	}

	return xboardInterface();


	ChessBoard board;
	board.initializeGame();

	if(false)
	{
		board.clearBoard();
		board.placePiece(Position(3, 3), WHITE_KING);
		board.placePiece(Position(3, 6), WHITE_PAWN);
		board.placePiece(Position(7, 3), BLACK_KING);
	}


	int counter = 0;

	// Shortest possible mate 13, 11, 17, 14

	for(int i = 0; i < 150; i++)
	{
		//board.printBoard();
		std::vector<Move> moves = board.legalMoves();
		if(moves.size() == 0)
		{
			printf("Black won\n");
			return 0;
		}
		Evaluation eval = board.dynamicEvaluation(3);
		printf("Performing move: %s (%s)\n\n", moves.at(board.bestMove).toString().c_str(), eval.toString().c_str());
		board.performBestMove();

		if(true)
		{
			board.printBoard();
			std::vector<Move> moves = board.legalMoves();
			board.printMovesFromList(moves);
			std::cout << "Enter move number: ";
			std::cin >> counter;
			if(counter <= (int) moves.size())
				board.performMove(moves.at(counter - 1));
		}
		else
		{
			//board.printBoard();
			moves = board.legalMoves();
			if(moves.size() == 0)
			{
				printf("White won\n");
				return 0;
			}
			eval = board.dynamicEvaluation(3);
			printf("Performing move: %s (%s)\n\n", moves.at(board.bestMove).toString().c_str(), eval.toString().c_str());
			board.performBestMove();
		}
	}
	return 0;

	while(true)
	{
		board.printBoard();
		std::vector<Move> moves = board.legalMoves();
		board.printMovesFromList(moves);
		std::cout << "Enter move number: ";
		std::cin >> counter;
		if(counter <= (int) moves.size())
			board.performMove(moves.at(counter - 1));
	}
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