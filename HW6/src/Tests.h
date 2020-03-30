/*
 * Tests.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef TESTS_H_
#define TESTS_H_

#include "EL.h"
#include "Board.h"
#include "Ship.h"

class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();
	bool testShipFunctions();
	bool testDisplayBoard();
	bool testProcessGuess();
	bool testHasLost();
};

#endif /* TESTS_H_ */
