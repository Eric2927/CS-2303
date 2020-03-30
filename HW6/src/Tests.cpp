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

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests()
{
	bool ok1 = testShipFunctions();
	bool ok2 = testDisplayBoard();
	bool ok3 = testProcessGuess();
	bool ok4 = testHasLost();
	bool answer = ok1 && ok2 && ok3 && ok4;
	return answer;
}

bool Tests::testShipFunctions() {
	bool works = true;
	// Since most ship functions are getters, those will not be tested

	// Test Function hit()
	Ship* aShip = new Ship(0);
	aShip->hit();
	// Case 1: Hit once
	if (aShip->numHits != 1) {
		works = false;
	}
	aShip->hit();
	aShip->hit();
	// Case 2: Hit multiple times
	if (aShip->numHits != 3) {
		works = false;
	}

	// Test Function isSunk()
	// Case 1: Not sunk
	if (aShip->isSunk() != false) {
		works = false;
	}
	aShip->hit();
	aShip->hit();
	// Case 2: Sunk
	if (aShip->isSunk() != true) {
		works = false;
	}

	if (works) {
		cout << "testShipFunctions passed" << endl;
	}
	else {
		cout << "testShipFunctions did not pass" << endl;
	}

	return works;
}

// Since this is a display function, the test will be based on programmer
// interpretation of console output.
bool Tests::testDisplayBoard() {
	bool works = true;

	srand(time(0));

	// Test case 1: For opponent
	Board* aBoard = new Board(true);
	cout << "What the ship layout actually is: " << endl;
	for (int row = 0; row < 10; row ++) {
		for (int col = 0; col < 10; col ++) {
			cout << aBoard->boardLayout[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "The board below should look like an empty board (or rather, a board full of water tiles only)." << endl;
	aBoard->displayBoard(&cout, true);

	// Test case 2: Not for opponent
	cout << endl;
	cout << "The board below here should look identical to the actual ship layout, except with row and column markings on the sides." << endl;
	aBoard->displayBoard(&cout, false);

	return works;

}

bool Tests::testProcessGuess() {
	bool works = true;

	// Manually arranges the board so that only one ship is on it
	Board* aBoard = new Board(true);
	Ship* aShip = new Ship(0);
	for (int row = 0; row < 10; row ++) {
		for (int col = 0; col < 10; col ++) {
			aBoard->boardLayout[row][col] = WATER_TILE;
			aBoard->shipLayout[row][col] = NULL;
		}
	}
	for (int i = 0; i < 5; i ++) {
		aBoard->ships[i] = NULL;
	}
	for (int row = 0; row < 5; row ++) {
		aBoard->boardLayout[row][0] = 'c';
		aBoard->shipLayout[row][0] = aShip;
	}
	aBoard->ships[0] = aShip;
	GuessStatus testResult;
	GuessStatus expectedResult;
	int row = -1;
	int col = -1;

	// Case 1: Guess is invalid (out of bounds)
	row = 12;
	col = 8;
	expectedResult = INVALID;
	testResult = aBoard->processGuess(row, col);
	if (testResult != expectedResult) {
		works = false;
	}

	// Case 2: Guess is invalid (has already been guessed)
	aBoard->boardLayout[1][3] = MISS_TILE;
	row = 1;
	col = 3;
	expectedResult = INVALID;
	testResult = aBoard->processGuess(row, col);
	if (testResult != expectedResult) {
		works = false;
	}

	// Case 3: Guess is a miss
	row = 9;
	col = 9;
	expectedResult = MISS;
	testResult = aBoard->processGuess(row, col);
	if (testResult != expectedResult) {
		works = false;
	}

	// Case 4: Guess is a hit
	row = 2;
	col = 0;
	expectedResult = HIT;
	testResult = aBoard->processGuess(row, col);
	if (testResult != expectedResult) {
		works = false;
	}

	// Case 5: Guess is a hit and sink
	aBoard->processGuess(0, 0);
	aBoard->processGuess(1, 0);
	aBoard->processGuess(3, 0);
	row = 4;
	col = 0;
	expectedResult = HITANDSUNK;
	testResult = aBoard->processGuess(row, col);
	cout << (int)testResult << endl;
	aBoard->displayBoard(&cout, false);
	if (testResult != expectedResult) {
		works = false;
	}

	if (works) {
		cout << "testProcessGuess passed" << endl;
	}
	else {
		cout << "testProcessGuess did not pass" << endl;
	}
	return works;
}

bool Tests::testHasLost() {
	bool works = true;

	Board* aBoard = new Board(true);

	// Case 1: Has not lost
	if (aBoard->hasLost() != false) {
		works = false;
	}
	aBoard->processGuess(3, 5);
	aBoard->processGuess(0, 7);
	aBoard->processGuess(1, 8);
	aBoard->processGuess(8, 6);
	aBoard->processGuess(2, 0);
	if (aBoard->hasLost() != false) {
		works = false;
	}

	// Case 2: Has lost
	for (int row = 0; row < 10; row ++) {
		for (int col = 0; col < 10; col ++) {
			aBoard->processGuess(row, col);
		}
	}
	if (aBoard->hasLost() != true) {
		works = false;
	}

	if (works) {
		cout << "testHasLost passed" << endl;
	}
	else {
		cout << "testHasLost did not pass" << endl;
	}

	return works;
}
