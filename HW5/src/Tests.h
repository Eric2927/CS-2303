/*
 * Tests.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef TESTS_H_
#define TESTS_H_

#include "EL.h"

class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();
	bool testWriteBoardToFile();
	bool testCanMove();
	bool testMovePiece();
	bool testMakeMove();
	bool testMakeMoveHelper(Board* board, Piece* piece, int finalRow, int finalCol, bool firstCall);
	bool testDisplayBoardToConsole();
};

#endif /* TESTS_H_ */
