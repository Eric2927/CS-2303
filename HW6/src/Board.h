/*
 * Board.h
 *
 *  Created on: Mar 2, 2020
 *      Author: eric_li
 */

#ifndef BOARD_H_
#define BOARD_H_
#include "EL.h"
#include "Ship.h"

const int BOARDSIZE = 10;

const int NUMSHIPS = 5;

// Characters on the battleship board
const char WATER_TILE = '~';
const char HIT_TILE = '*';
const char MISS_TILE = 'm';

class Board {
private:
	char boardLayout[BOARDSIZE][BOARDSIZE];
	Ship* shipLayout[BOARDSIZE][BOARDSIZE];
	Ship* ships[NUMSHIPS];
public:
	Board(bool random);
	virtual ~Board();
	GuessStatus processGuess(int row, int col);
	bool hasLost();
	void displayBoard(ostream* stream, bool forOpponent);
	void displaySinkMessage(int row, int col, ostream* outStream);
	friend class Tests;
};

#endif /* BOARD_H_ */
