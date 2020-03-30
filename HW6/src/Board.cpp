/*
 * Board.cpp
 *
 *  Created on: Mar 2, 2020
 *      Author: eric_li
 */

#include "Board.h"

Board::Board(bool random) {
	// Initializes board layout to a water tiles
	for (int row = 0; row < BOARDSIZE; row ++) {
		for (int col = 0; col < BOARDSIZE; col ++) {
			boardLayout[row][col] = WATER_TILE;
		}
	}

	if (random) {
		// If random generation, loop through every ship
		for (int i = 0; i < NUMSHIPS; i ++) {
			ships[i] = new Ship(i);		// Specific ship is initialized (check ship constructor for details)
			// 50-50 chance for horizontal placement or vertical placement
			if (rand() % 2) {
				// If horizontal placement
				bool validLocation = false;
				int row = -1;
				int col = -1;
				while (!validLocation) {
					// Generates a random location on the board representing the left end of a horizontal ship.
					// Specifically tailored to generate a position for a ship fully in bounds
					row = rand() % BOARDSIZE;
					col = rand() % (BOARDSIZE - ships[i]->getLength() + 1);
					validLocation = true; // assumption
					// Checks if there is already another ship in the way
					for (int j = 0; (j < ships[i]->getLength()) && validLocation; j++) {
						if (boardLayout[row][col + j] != WATER_TILE) {
							validLocation = false;
						}
					}
				}
				//cout << ships[i]->getName() << " (Horizontal): " << row << ", " << col << endl;
				// Puts the ship on the board at a valid random location horizontally
				for (int k = 0; k < ships[i]->getLength(); k ++) {
					boardLayout[row][col + k] = ships[i]->getSymbol();
					shipLayout[row][col + k] = ships[i];
				}
			}
			else {
				// If vertical placement
				bool validLocation = false;
				int row = -1;
				int col = -1;
				while (!validLocation) {
					// Generates a random location on the board representing the top end of a vertical ship.
					// Specifically tailored to generate a position for a ship fully in bounds
					row = rand() % (BOARDSIZE - ships[i]->getLength() + 1);
					col = rand() % BOARDSIZE;
					validLocation = true;	// assumption
					// Checks if there is already another ship in the way
					for (int j = 0; (j < ships[i]->getLength()) && validLocation; j++) {
						if (boardLayout[row + j][col] != WATER_TILE) {
							validLocation = false;
						}
					}
				}
				//cout << ships[i]->getName() << " (Vertical): " << row << ", " << col << endl;
				// Puts the ship on the board at a valid random location horizontally
				for (int k = 0; k < ships[i]->getLength(); k ++) {
					boardLayout[row + k][col] = ships[i]->getSymbol();
					shipLayout[row + k][col] = ships[i];
				}
			}
		}
	}
	else {
		for (int i = 0; i < NUMSHIPS; i ++) {
			cout << "Current Board: " << endl;
			displayBoard(&cout, false);
			ships[i] = new Ship(i);

			// Prompt user for valid orientation
			bool validOrientation = false;
			int orientation;
			while (!validOrientation) {
				cout << "How would you like to place your " << ships[i]->getName() << "? Enter 1 for horizontal and 2 for vertical." << endl;
				cin >> orientation;
				if (orientation == 1 || orientation == 2) {
					validOrientation = true;
				}
				else {
					cout << "You did not enter a valid orientation. Try again." << endl;
				}
			}

			// Prompt user for valid location
			bool validLocation = false;
			int row;
			int col;
			while (!validLocation) {
				cout << "Where would you like to place your " << ships[i]->getName() << "?" << endl <<
						"If you chose to place your ship horizontally, please enter the coordinate of the left end." << endl <<
						"If you chose to place your ship vertically, please enter the coordinate of the top end." << endl;
				cout << "Row: ";
				cin >> row;
				cout << "Column: ";
				cin >> col;
				validLocation = true; // assumption
				// Horizontal orientation
				if (orientation == 1) {
					// check if there is another ship in the way
					for (int j = 0; (j < ships[i]->getLength()) && validLocation; j++) {
						if (boardLayout[row][col + j] != WATER_TILE) {
							validLocation = false;
						}
					}
				}
				// Vertical orientation
				else {
					// check if there is another ship in the way
					for (int j = 0; (j < ships[i]->getLength()) && validLocation; j++) {
						if (boardLayout[row + j][col] != WATER_TILE) {
							validLocation = false;
						}
					}
				}
				if (!validLocation) {
					cout << "You did not enter a valid coordinate to place the ship. Try again." << endl;
				}
			}

			// Place the ship based on orientation
			if (orientation == 1) {
				for (int k = 0; k < ships[i]->getLength(); k ++) {
					boardLayout[row][col + k] = ships[i]->getSymbol();
					shipLayout[row][col + k] = ships[i];
				}
			}
			else {
				for (int k = 0; k < ships[i]->getLength(); k ++) {
					boardLayout[row + k][col] = ships[i]->getSymbol();
					shipLayout[row + k][col] = ships[i];
				}
			}
		}
	}
}

Board::~Board() {
	for (int row = 0; row < BOARDSIZE; row ++) {
		for (int col = 0; col < BOARDSIZE; col ++) {
			delete shipLayout[row][col];
		}
	}
	for (int i = 0; i < NUMSHIPS; i ++) {
		delete ships[i];
	}
}

GuessStatus Board::processGuess(int row, int col) {
	char symbolAtGuess = boardLayout[row][col];
	GuessStatus guessResult;

	// Check if guess is in bounds
	if (row < 0 || row >= BOARDSIZE ||
			col < 0 || col >= BOARDSIZE) {
		guessResult = INVALID;
	}
	else {
		switch (symbolAtGuess) {
		// If the location guessed has a ship
		case 'c':
		case 'b':
		case 'r':
		case 's':
		case 'd':
			guessResult = HIT;
			shipLayout[row][col]->hit();
			// If ship sunk (also, shipLayout should not be null at the coordinate, but just in case)
			if (shipLayout[row][col] != NULL && shipLayout[row][col]->isSunk()) {
				guessResult = HITANDSUNK;
			}
			boardLayout[row][col] = HIT_TILE;		// Marks the guess location on the board with a hit
			break;

			// If the location guessed does not have a ship
		case WATER_TILE:
			guessResult = MISS;
			boardLayout[row][col] = MISS_TILE;		// Marks the guess location on the board with a miss
			break;

			// If the location guessed is invalid
		case HIT_TILE:
		case MISS_TILE:
		default:
			guessResult = INVALID;
			break;
		}
	}
	return guessResult;
}

bool Board::hasLost() {
	bool hasLost = true;
	for (int i = 0; i < NUMSHIPS; i ++) {
		hasLost = hasLost && ships[i]->isSunk();
	}
	return hasLost;
}

void Board::displayBoard(ostream* stream, bool forOpponent) {
	if (forOpponent) {
		*stream << "  0 1 2 3 4 5 6 7 8 9" << endl;		// Top row, to help user determine columns of each cell
		// Looping through board layout
		for (int row = 0; row < BOARDSIZE; row ++) {
			*stream << row;		// First print out row number, to help user determine rows of each cell
			// Now loops through contents of each row
			for (int col = 0; col < BOARDSIZE; col ++) {
				char tile = boardLayout[row][col];
				// If the tile has a ship that has not been hit, mark it as a water tile instead
				switch (tile) {
				case 'c':
				case 'b':
				case 'r':
				case 's':
				case 'd':
					tile = WATER_TILE;
					break;
				default:
					// Tile can stay the actual ship
					break;
				}
				*stream << " " << tile;		// Prints the tile character
			}
			*stream << endl;		// Moves on to the next row
		}
	}
	else {
		*stream << "  0 1 2 3 4 5 6 7 8 9" << endl;		// Top row, to help user determine column of each cell
		for (int row = 0; row < BOARDSIZE; row ++) {
			*stream << row;		// First print out row number, to help user determine rows of each cell
			for (int col = 0; col < BOARDSIZE; col ++) {
				*stream << " " << boardLayout[row][col];	// print out contents of each cell
			}
			*stream << endl;	// Move on to next row
		}
	}
}

void Board::displaySinkMessage(int row, int col, ostream* outStream) {
	Ship* sunkShip = shipLayout[row][col];
	if (sunkShip != NULL) {
		*outStream << sunkShip->getName() << " has sunk." << endl;
	}
	else {
		*outStream << "There is no ship at row " << row << ", column " << col << endl;
	}
}
