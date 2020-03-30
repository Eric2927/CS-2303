/*
 * Tests.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Tests.h"
#include <stdbool.h>

Tests::Tests() {
	// TODO Auto-generated constructor stub
	srand(time(0));
}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests()
{
	bool answer = true;
	bool ok1 = testWriteBoardToFile();
	bool ok2 = testCanMove();
	bool ok3 = testMovePiece();
	bool ok4 = testMakeMove();
	bool ok5 = testDisplayBoardToConsole();
	answer = ok1 && ok2 && ok3 && ok4 && ok5;
	return answer;
}

// The best way to check if this works is to visually interpret a console result.
// There is no simple way to check.
bool Tests::testWriteBoardToFile() {
	bool works = true;
	Board* myBoard = new Board();	// The constructor writes the starting board to the file.
	ifstream inFile;
	inFile.open("moveLog.txt");
	string line;
	cout << "The diagram below should look like the starting arrangement of a checkers game." << endl;
	while (!inFile.eof()) {
		getline(inFile, line);
		cout << line << endl;
	}
	return works;
}

bool Tests::testCanMove() {
	bool works = true;
	Board* myBoard = new Board("startingBoard.txt", "moveLog.txt", true);
	int dimensions = 8;

	// Case 1: Piece cannot move due to being on the edge of board
	int row = 0;
	int col = 3;
	if (myBoard->canMove(myBoard->boardLayout[row*dimensions + col], 0) != 0) {
		works = false;
	}

	// Case 2: Piece cannot move due to a friendly piece being in the way
	row = 3;
	col = 6;
	if (myBoard->canMove(myBoard->boardLayout[row*dimensions + col], 3) != 0) {
		works = false;
	}

	// Case 3: Piece can move because of empty diagonal square in front of it
	if (myBoard->canMove(myBoard->boardLayout[row*dimensions + col], 2) != 1) {
		works = false;
	}

	// Case 4: Pawn can't move backwards
	row = 5;
	col = 2;
	if (myBoard->canMove(myBoard->boardLayout[row*dimensions + col], 2) != 0) {
		works = false;
	}

	// Case 5: Piece can jump and eliminate enemy
	row = 7;
	col = 2;
	if (myBoard->canMove(myBoard->boardLayout[row*dimensions + col], 1) != 2) {
		works = false;
	}

	// Case 6: King can move backwards
	row = 0;
	col = 1;
	if (myBoard->canMove(myBoard->boardLayout[row*dimensions + col], 3) != 1) {
		works = false;
	}

	if (works) {
		cout << "testCanMove passed" << endl;
	}
	else {
		cout << "testCanMove did not pass" << endl;
	}
	return works;
}

bool Tests::testMovePiece() {
	bool works = true;
	Board* myBoard = new Board("startingBoard.txt", "moveLog.txt", true);

	// Case 1: Normal one-space move
	int dimensions = 8;
	int row = 3;
	int col = 6;
	Piece* pieceToMove = myBoard->boardLayout[row*dimensions + col];
	myBoard->movePiece(pieceToMove, 2, false);
	if (myBoard->boardLayout[(row+1)*dimensions + (col-1)] != pieceToMove) {
		works = false;
	}
	if (myBoard->boardLayout[row*dimensions + col] != NULL) {
		works = false;
	}
	if ((pieceToMove->row != row + 1) || (pieceToMove->col != col - 1)) {
		works = false;
	}

	// Case 2: Jump
	row = 7;
	col = 2;
	pieceToMove = myBoard->boardLayout[row*dimensions + col];
	Piece* pieceToEliminate = myBoard->boardLayout[(row-1)*dimensions + (col+1)];
	myBoard->movePiece(pieceToMove, 1, true);
	if (myBoard->boardLayout[(row-2)*dimensions + (col+2)] != pieceToMove) {
		works = false;
	}
	if (myBoard->boardLayout[row*dimensions + col] != NULL) {
		works = false;
	}
	if ((pieceToMove->row != row - 2) || (pieceToMove->col != col + 2)) {
		works = false;
	}
	if (myBoard->boardLayout[(row-1)*dimensions + (col+1)] != NULL) {
		works = false;
	}
	if (!pieceToEliminate->isDead) {
		works = false;
	}

	if (works) {
		cout << "testMovePiece passed" << endl;
	}
	else {
		cout << "testMovePiece did not pass" << endl;
	}
	return works;
}


bool Tests::testMakeMove() {
	bool works = true;
	Board* originalBoard = new Board("startingBoard.txt", "moveLog.txt", false);
	Board* newBoard = new Board("startingBoard.txt", "moveLog.txt", false);
	Piece* movedPiece = NULL;
	int direction = -1;
	bool moveWasMade = false;
	bool jump = false;
	newBoard->makeMove();
	// Loops through every white piece (white's turn) to see which piece was moved
	for (int i = 0; i < originalBoard->TOTALSTARTINGPIECES/2; i ++) {
		// Checks if the white piece of interest is not the same on the original and new boards
		if ((originalBoard->whitePieces[i] != NULL) &&
				((originalBoard->whitePieces[i]->row != newBoard->whitePieces[i]->row) ||
						(originalBoard->whitePieces[i]->col != newBoard->whitePieces[i]->col))) {
			// if so, then the moved piece has been found
			movedPiece = originalBoard->whitePieces[i];
			// Tests each type of one-square diagonal move first
			// Upper left
			if (newBoard->whitePieces[i]->row == movedPiece->row - 1 && newBoard->whitePieces[i]->col == movedPiece->col - 1) {
				direction = 0;
			}
			// Upper right
			else if (newBoard->whitePieces[i]->row == movedPiece->row - 1 && newBoard->whitePieces[i]->col == movedPiece->col + 1) {
				direction = 1;
			}
			// Lower left
			else if (newBoard->whitePieces[i]->row == movedPiece->row + 1 && newBoard->whitePieces[i]->col == movedPiece->col - 1) {
				direction = 2;
			}
			// Lower right
			else if (newBoard->whitePieces[i]->row == movedPiece->row + 1 && newBoard->whitePieces[i]->col == movedPiece->col + 1) {
				direction = 3;
			}
			// If not a one-square diagonal move, then a jump must've occured
			else {
				jump = true;
				Board* testBoard = new Board("startingBoard.txt", "moveLog.txt", false);
				Piece* temp = testBoard->whitePieces[i];
				works = testMakeMoveHelper(testBoard, temp, newBoard->whitePieces[i]->row, newBoard->whitePieces[i]->col, true);
			}
			moveWasMade = true;
		}
	}
	// If not a jump, just call the canMove function, which has already been tested before
	if (!jump) {
		if (originalBoard->canMove(movedPiece, direction) == 0) {
			works = false;
		}
	}

	if (works) {
		cout << "testMakeMove passed" << endl;
	}
	else {
		cout << "testMakeMove did not pass" << endl;
	}
	return works;
}

/**
 * This method basically takes the given piece and tries to find every possible way it can jump (including multiple jumps)
 * and sees if it can end up at the given finalRow and finalCol. If not, then returns false. If so, returns true.
 */
bool Tests::testMakeMoveHelper(Board* board, Piece* piece, int finalRow, int finalCol, bool firstCall) {
	Board* currentBoard = board;
	Piece* movingPiece = piece;
	if (firstCall) {
		currentBoard = new Board("startingBoard.txt", "moveLog.txt", false);
		for (int i = 0; i < currentBoard->TOTALSTARTINGPIECES/2; i ++) {
			if (piece->row == currentBoard->whitePieces[i]->row && piece->col == currentBoard->whitePieces[i]->col) {
				movingPiece = currentBoard->whitePieces[i];
			}
		}
	}
	bool matchesFinalLocation = false;
	if (piece->row == finalRow && piece->col == finalCol) {
		matchesFinalLocation = true;
	}
	for (int dir = 0; dir < 4; dir ++) {
		if (currentBoard->canMove(movingPiece, dir) == 2 && !matchesFinalLocation) {
			currentBoard->movePiece(movingPiece, dir, true);
			matchesFinalLocation = testMakeMoveHelper(currentBoard, movingPiece, finalRow, finalCol, false);
		}
	}
	return matchesFinalLocation;
}

// Similar to testWriteBoardToFile, this test will have to depend on a human
// reading the console and determing if the test passes or not.
bool Tests::testDisplayBoardToConsole() {
	bool works = true;
	Board* aBoard = new Board();
	cout << "The diagram below should also look like the starting arrangement of a checkers game. If not, the test does not pass." << endl;
	aBoard->displayBoardToConsole();
	return works;
}

