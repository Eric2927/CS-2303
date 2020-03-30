/*
 * Production.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Production.h"
#include <stdbool.h>

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[])
{
	bool answer = false;
	if (argc <= 1) {
		cout << "Didn't find any interesting arguments" << endl;
		answer = false;
	}
	else if (argc == 2) {
		cout << "Please provide an input file name and an output file name" << endl;
		answer = false;
	}
	else if (argc == 3) {
		cout << "Please provide an output file name" << endl;
		answer = false;
	}
	else {
		answer = true;
		cout << "Found " << argc - 1 << " interesting arguments." << endl;
		const int MAXFILENAMELENGTH = 50;
		char inputFilename[MAXFILENAMELENGTH];
		char outputFilename[MAXFILENAMELENGTH];
		char* endPtr = new char;
		int maxMoves = -1;
		for (int i = 1; i < argc; i ++) {
			switch (i) {
			case 1:
				maxMoves = strtol(argv[i], &endPtr, 10);
				if (maxMoves <= 0) {
					cout << "Max moves provided is 0 or less. Game will not be executed." << endl;
					answer = false;
				}
				else {
					cout << "Maximum number of moves allowed: " << maxMoves << endl;
				}
				break;
			case 2:
				if (strlen(argv[i]) >= MAXFILENAMELENGTH) {
					cout << "Input Filename is too long." << endl;
					answer = false;
				}
				else {
					strcpy(inputFilename, argv[i]);
					cout << "Input filename is " << inputFilename << endl;
				}
				break;
			case 3:
				if (strlen(argv[i]) >= MAXFILENAMELENGTH) {
					cout << "Output Filename is too long." << endl;
					answer = false;
				}
				else {
					strcpy(outputFilename, argv[i]);
					cout << "Output filename is " << outputFilename << endl;
				}
				break;
			}
		}
		if (answer) {
			int moves = 0;
			Board* aBoard = new Board(inputFilename, outputFilename, true);
			cout << "Starting Board:" << endl;
			aBoard->displayBoardToConsole();
			while (!aBoard->makeMove() && moves < maxMoves) {
				aBoard->displayBoardToConsole();
				moves ++;
			}
		}
	}
	return answer;
}

