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
	void writeBorderToFile(ostream* outputStream);
	void writeEmptyPartOfRowToFile(ostream* outputStream);
	void writeRowContentToFile(int row, ostream* outputStream);
	friend class Tests;		// makes writing test cases possible
public:
	Board();
	Board(char* inputFilename, char* outputFilename, bool isBlackTurn);
	virtual ~Board();
	void writeBoardToFile();
	void displayBoardToConsole();
	bool makeMove();
	int canMove(Piece* aPiece, int direction);
	void movePiece(Piece* aPiece, int direction, bool jump);
};

#endif /* BOARD_H_ */
