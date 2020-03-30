/*
 * Production.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Production.h"

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[])
{
	bool answer = true;

	// Quick note here, I don't believe there is any use of command line arguments for this game.
	// The only user input should be for guessing where to hit next.
	// The github implementation linked on the homework description also did not use
	// any external input besides user guesses, thus I have not implemented any command line interpretations in this assignment.
	srand(time(0));

	char* filename = "gamelog.txt";
	ofstream outFileStream;
	outFileStream.open(filename);

	cout << "Welcome to Battleship" << endl;

	Board* cpuBoard = new Board(true);

	// Prompt user for manual/random placement of ships on their own board
	int placement = -1;
	// Keep prompting until user gives valid nput
	while (placement != 1 && placement != 2) {
		cout << "Would you like to manually place the ships on your board or have them randomly placed?" << endl;
		cout << "Please enter 1 if you would prefer manual placement, 2 if you prefer random placement." << endl;
		cin >> placement;
		if (placement != 1 && placement != 2) {
			cout << "You did not enter a valid placement type." << endl;
		}
	}

	// Depending on the placement choice, the constructor is called with a different argument
	Board* userBoard;
	if (placement == 1) {
		// Manual placement
		userBoard = new Board(false);
	}
	else {
		// Random placement
		userBoard = new Board(true);
	}

	// Prints starting board configurations of both teams to log file
	// Note: I am assuming that the user is not (or cannot) access the log
	// file until after the game, since it will reveal the cpu's ship positioning.
	// This log is intended for view after the conclusion of the game.
	outFileStream << "User's starting board: " << endl;
	userBoard->displayBoard(&outFileStream, false);
	outFileStream << "CPU's starting board: " << endl;
	cpuBoard->displayBoard(&outFileStream, false);
	outFileStream << endl << endl;

	bool isUserTurn = rand() % 2;	// Randomly chooses who goes first
	bool gameIsOver = false;

	int turnCounter = 1;		// Starts at turn 1, not turn 0

	while (!gameIsOver) {
		// Will store user guess
		int row = -1;
		int col = -1;
		outFileStream << "==========TURN " << turnCounter << "==========" << endl;
		cout << "==========TURN " << turnCounter << "==========" << endl;
		if (isUserTurn) {
			outFileStream << "USER'S TURN" << endl;
			cout << "USER'S TURN" << endl;
			cout << "CPU's Board (Pre-Guess): " << endl;
			cpuBoard->displayBoard(&cout, true);
			GuessStatus guessResult = INVALID;
			// Keeps prompting user for a row and column guess until a valid guess is given
			while (guessResult == INVALID) {
				cout << "Please enter your guess." << endl;
				cout << "Row: ";
				cin >> row;
				cout << "Column: ";
				cin >> col;
				guessResult = cpuBoard->processGuess(row, col);		// guess is processed and the result is stored in guessResult
				switch (guessResult) {
				case INVALID:
					// If guess was invalid, user is notified and will be reprompted
					cout << "Row " << row << ", column " << col << "is not valid coordinate. Make sure you have not guessed it once already." << endl;
					break;
				case MISS:
					// If guess is a miss, user is notified accordingly and log file is updated accordingly
					cout << "Row " << row << ", column " << col << " is a miss." << endl;
					outFileStream << "User guesses row " << row << ", column " << col << endl;
					outFileStream << "It was a miss!" << endl;
					break;
				case HIT:
					// If guess is a hit, user is notified accordingly and log file is updated accordingly
					cout << "Row " << row << ", column " << col << " is a hit!" << endl;
					outFileStream << "User guesses row " << row << ", column " << col << endl;
					outFileStream << "It was a hit!" << endl;
					break;
				case HITANDSUNK:
					// If guess is hit and a ship was sunkas as a reseult, user is notified accordingly and log file is updated accordingly
					cout << "Row " << row << ", column " << col << " is a hit! The cpu's ";
					cpuBoard->displaySinkMessage(row, col, &cout);
					outFileStream << "User guesses row " << row << ", column " << col << endl;
					outFileStream << "It was a hit! The cpu's ";
					cpuBoard->displaySinkMessage(row, col, &outFileStream);
					break;
				}
			}
			cout << "CPU's Board (Post-Guess): " << endl;
			cpuBoard->displayBoard(&cout, true);
			outFileStream << "CPU's Board (Post-Guess): " << endl;
			cpuBoard->displayBoard(&outFileStream, false);
		}
		else {
			outFileStream << "CPU'S TURN" << endl;
			cout << "CPU's TURN" << endl;
			int boardSize = 10;		// dimensions of board
			GuessStatus guessResult = INVALID;
			// Keep generating random numbers for a guess until a valid one is found
			while (guessResult == INVALID) {
				row = rand() % boardSize;
				col = rand() % boardSize;
				guessResult = userBoard->processGuess(row, col);
			}
			cout << "CPU guesses row " << row << ", column " << col << endl;
			outFileStream << "CPU guesses row " << row << ", column " << col << endl;
			switch (guessResult) {
			case MISS:
				// If cpu guess is a miss, user is notified and log file is updated accordingly
				cout << "It was a miss!" << endl;
				outFileStream << "It was a miss!" << endl;
				break;
			case HIT:
				// If cpu guess is a hit, user is notified and log file is updated accordingly
				cout << "It was a hit!" << endl;
				outFileStream << "It was a hit!" << endl;
				break;
			case HITANDSUNK:
				// If cpu guess is a hit and a ship was sunk as a result, user is notified and log file is updated accordingly
				cout << "It was a hit! The user's ";
				userBoard->displaySinkMessage(row, col, &cout);
				cout << "It was a hit! THe user's ";
				userBoard->displaySinkMessage(row, col, &outFileStream);
				break;
			}
			cout << "Player's Board (Post-Guess): " << endl;
			userBoard->displayBoard(&cout, false);
			outFileStream << "User's Board (Post-Guess): " << endl;
			userBoard->displayBoard(&outFileStream, false);
		}
		turnCounter ++;		// One turn has been executed

		// Formatting stuff
		cout << endl;
		outFileStream << endl;

		isUserTurn = !isUserTurn;	// Will be other player's turn next iteration
		gameIsOver = userBoard->hasLost() && cpuBoard->hasLost();		// updates gameIsOver's status upon turn execution
	}

	if (userBoard->hasLost()) {
		cout << "You have lost! Try again next time." << endl;
		outFileStream << "The user has lost." << endl;
	}
	else if (cpuBoard->hasLost()) {
		cout << "You have won! Congrats." << endl;
		outFileStream << "The user has won." << endl;
	}
	else {
		cout << "Something went wrong." << endl;
	}

	outFileStream.close();

	return answer;

}

