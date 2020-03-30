/*
 * Board.h
 *
 *  Created on: Feb 29, 2020
 *      Author: eric_li
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "EL.h"

using namespace std;

struct Piece {
	bool isRoyalty;
	bool isDead;
	bool isBlack;
	int row;
	int col;
};

class Board {
private:
	static const int TOTALSTARTINGPIECES = 24;
	static const int BOARDDIMENSIONS = 8;
	char* outputFilename;
	ofstream* outputFileStream;
	Piece* blackPieces[TOTALSTARTINGPIECES/2];
	Piece* whitePieces[TOTALSTARTINGPIECES/2];
	Piece* boardLayout[BOARDDIMENSIONS*BOARDDIMENSIONS];	// In theory, not needed to function, but it speeds up the displayBoard() function
	bool isBlackTurn;

	// Helpers for any method that displays the board
	void writeBorderToFile(ostream* outputStream);
	void writeEmptyPartOfRowToFile(ostream* outputStream);
	void writeRowContentToFile(int row, ostream* outputStream);

	friend class Tests;		// makes writing test cases possible
public:
	Board();
	Board(char* inputFilename, char* outputFilename, bool isBlackTurn);
	virtual ~Board();
	void writeBoardToFile();			// writes the current board to the log file
	void displayBoardToConsole();			// displays board to console
	bool makeMove();				// executes a turn of the game
	int canMove(Piece* aPiece, int direction);			// checks whether a piece can move in the given direction
	void movePiece(Piece* aPiece, int direction, bool jump);		// moves a piece in the given direction
};

#endif /* BOARD_H_ */
