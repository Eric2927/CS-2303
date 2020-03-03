/*
 * Board.cpp
 *
 *  Created on: Feb 29, 2020
 *      Author: eric_li
 */

#include "Board.h"

Board::Board() {
	for (int i = 0; i < BOARDDIMENSIONS; i ++) {
		for (int j = 0; j < BOARDDIMENSIONS; j ++) {
			boardLayout[i*BOARDDIMENSIONS + j] = NULL;
		}
	}
	outputFilename = "moveLog.txt";
	outputFileStream = new ofstream();
	outputFileStream->open(outputFilename);
	isBlackTurn = true;
	int blackRow = 5;
	int blackCol = 0;
	int whiteRow = 0;
	int whiteCol = 1;
	for (int i = 0; i < TOTALSTARTINGPIECES / 2; i ++) {
		blackPieces[i] = new Piece();
		blackPieces[i]->isDead = false;
		blackPieces[i]->isRoyalty = false;
		blackPieces[i]->isBlack = true;
		blackPieces[i]->row = blackRow;
		blackPieces[i]->col = blackCol;
		boardLayout[blackRow*BOARDDIMENSIONS + blackCol] = blackPieces[i];
		blackCol += 2;
		if (blackCol >= BOARDDIMENSIONS) {
			blackRow ++;
			if (blackRow % 2 == 0) {
				blackCol = 1;
			}
			else {
				blackCol = 0;
			}
		}
		whitePieces[i] = new Piece();
		whitePieces[i]->isDead = false;
		whitePieces[i]->isRoyalty = false;
		whitePieces[i]->isBlack = false;
		whitePieces[i]->row = whiteRow;
		whitePieces[i]->col = whiteCol;
		boardLayout[whiteRow*BOARDDIMENSIONS + whiteCol] = whitePieces[i];
		whiteCol += 2;
		if (whiteCol >= BOARDDIMENSIONS) {
			whiteRow ++;
			if (whiteRow % 2 == 0) {
				whiteCol = 1;
			}
			else {
				whiteCol = 0;
			}
		}
	}
	*outputFileStream << "Starting Board" << endl;
	writeBoardToFile();
}

Board::Board(char* inputFilename, char* outputFilename, bool isBlackTurn) {
	this->isBlackTurn = isBlackTurn;
	for (int i = 0; i < BOARDDIMENSIONS; i ++) {
		for (int j = 0; j < BOARDDIMENSIONS; j ++) {
			boardLayout[i*BOARDDIMENSIONS + j] = NULL;
		}
	}
	this->outputFilename = outputFilename;
	outputFileStream = new ofstream();
	outputFileStream->open(outputFilename);
	ifstream inFile;
	inFile.open(inputFilename);
	bool allInformationIsObtained = false;
	int i = 0;
	string garbageDump;
	while (!inFile.eof() && !allInformationIsObtained) {
		switch (inFile.peek()) {
		case 'B':
			inFile.ignore(1, '\n');
			inFile.ignore(1);
			while (inFile.peek() != '#') {
				blackPieces[i] = new Piece();
				blackPieces[i]->isRoyalty = true;
				blackPieces[i]->isDead = false;
				blackPieces[i]->isBlack = true;
				inFile >> blackPieces[i]->row;
				inFile >> blackPieces[i]->col;
				boardLayout[blackPieces[i]->row*BOARDDIMENSIONS + blackPieces[i]->col] = blackPieces[i];
				inFile.ignore(1, '\n');
				i ++;
				//cout << "B" << endl;
				//cout << blackPieces[i]->row << " " << blackPieces[i]->col << endl;
			}
			getline(inFile, garbageDump);
			getline(inFile, garbageDump);
			break;
		case 'b':
			inFile.ignore(1, '\n');
			inFile.ignore(1);
			while (inFile.peek() != '#') {
				blackPieces[i] = new Piece();
				blackPieces[i]->isRoyalty = false;
				blackPieces[i]->isDead = false;
				blackPieces[i]->isBlack = true;
				inFile >> blackPieces[i]->row;
				inFile >> blackPieces[i]->col;
				boardLayout[blackPieces[i]->row*BOARDDIMENSIONS + blackPieces[i]->col] = blackPieces[i];
				inFile.ignore(1, '\n');
				i ++;
				//cout << "b" << endl;
				//cout << blackPieces[i]->row << " " << blackPieces[i]->col << endl;
			}
			while (i < TOTALSTARTINGPIECES/2) {
				blackPieces[i] = new Piece();
				blackPieces[i]->isDead = true;
				i ++;
			}
			getline(inFile, garbageDump);
			getline(inFile, garbageDump);
			i = 0;
			break;
		case 'W':
			inFile.ignore(1, '\n');
			inFile.ignore(1);
			while (inFile.peek() != '#') {
				whitePieces[i] = new Piece();
				whitePieces[i]->isRoyalty = true;
				whitePieces[i]->isDead = false;
				whitePieces[i]->isBlack = false;
				inFile >> whitePieces[i]->row;
				inFile >> whitePieces[i]->col;
				boardLayout[whitePieces[i]->row*BOARDDIMENSIONS + whitePieces[i]->col] = whitePieces[i];
				inFile.ignore(1, '\n');
				i ++;
				//cout << "W" << endl;
				//cout << whitePieces[i]->row << " " << whitePieces[i]->col << endl;
			}
			getline(inFile, garbageDump);
			getline(inFile, garbageDump);
			break;
		case 'w':
			inFile.ignore(1, '\n');
			inFile.ignore(1);
			while (inFile.peek() != '#') {
				whitePieces[i] = new Piece();
				whitePieces[i]->isRoyalty = false;
				whitePieces[i]->isDead = false;
				whitePieces[i]->isBlack = false;
				inFile >> whitePieces[i]->row;
				inFile >> whitePieces[i]->col;
				boardLayout[whitePieces[i]->row*BOARDDIMENSIONS + whitePieces[i]->col] = whitePieces[i];
				inFile.ignore(1, '\n');
				i ++;
				//cout << "w" << endl;
				//cout << whitePieces[i]->row << " " << whitePieces[i]->col << endl;
			}
			while (i < TOTALSTARTINGPIECES/2) {
				whitePieces[i] = new Piece();
				whitePieces[i]->isDead = true;
				i ++;
			}
			allInformationIsObtained = true;
			break;
		}
	}
	*outputFileStream << "Starting Board" << endl;
	writeBoardToFile();
}

Board::~Board() {
	for (int i = 0; i < TOTALSTARTINGPIECES/2; i ++) {
		delete blackPieces[i];
		delete whitePieces[i];
	}
	for (int i = 0; i < BOARDDIMENSIONS*BOARDDIMENSIONS; i ++) {
		delete boardLayout[i];
	}
	outputFileStream->close();
}

void Board::writeBorderToFile(ostream* outputStream) {
	int i = 0;
	while (i < 49) {
		*outputStream << "@";
		i ++;
	}
	*outputStream << endl;
}

void Board::writeEmptyPartOfRowToFile(ostream* outputStream) {
	int i = 0;
	while (i < 8) {
		*outputStream << "@";
		*outputStream << "     ";
		i ++;
	}
	*outputStream << "@";
	*outputStream << endl;
}

void Board::writeRowContentToFile(int row, ostream* outputStream) {
	int col = 0;
	while (col < 8) {
		*outputStream << "@  ";
		if (boardLayout[row*BOARDDIMENSIONS + col] == NULL) {
			*outputStream << " ";
		}
		else {
			if (boardLayout[row*BOARDDIMENSIONS + col]->isRoyalty) {
				if (boardLayout[row*BOARDDIMENSIONS + col]->isBlack) {
					*outputStream << "B";
				}
				else {
					*outputStream << "W";
				}
			}
			else {
				if (boardLayout[row*BOARDDIMENSIONS + col]->isBlack) {
					*outputStream << "b";
				}
				else {
					*outputStream << "w";
				}
			}
		}
		*outputStream << "  ";
		col ++;
	}
	*outputStream << "@";
	*outputStream << endl;
}

void Board::writeBoardToFile() {
	int i = 0;
	while (i < 8) {
		writeBorderToFile(outputFileStream);
		writeEmptyPartOfRowToFile(outputFileStream);
		writeRowContentToFile(i, outputFileStream);
		writeEmptyPartOfRowToFile(outputFileStream);
		i ++;
	}
	writeBorderToFile(outputFileStream);
}

void Board::movePiece(Piece* aPiece, int direction, bool jump) {
	switch (direction) {
	// Upper left
	case 0:
		if (jump) {
			if (aPiece->isBlack) {
				*outputFileStream << "Black jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 2 << " " << aPiece->col - 2 << ")." << endl;
			}
			else {
				*outputFileStream << "White jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 2 << " " << aPiece->col - 2 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			boardLayout[(aPiece->row-1)*BOARDDIMENSIONS + (aPiece->col-1)]->isDead = true;
			boardLayout[(aPiece->row-1)*BOARDDIMENSIONS + (aPiece->col-1)] = NULL;
			aPiece->row -= 2;
			aPiece->col -= 2;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		else {
			if (aPiece->isBlack) {
				*outputFileStream << "Black moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 1 << " " << aPiece->col - 1 << ")." << endl;
			}
			else {
				*outputFileStream << "White moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 1 << " " << aPiece->col - 1 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			aPiece->row -= 1;
			aPiece->col -= 1;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		break;
		// Upper right
	case 1:
		if (jump) {
			if (aPiece->isBlack) {
				*outputFileStream << "Black jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 2 << " " << aPiece->col + 2 << ")." << endl;
			}
			else {
				*outputFileStream << "White jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 2 << " " << aPiece->col + 2 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			boardLayout[(aPiece->row-1)*BOARDDIMENSIONS + (aPiece->col+1)]->isDead = true;
			boardLayout[(aPiece->row-1)*BOARDDIMENSIONS + (aPiece->col+1)] = NULL;
			aPiece->row -= 2;
			aPiece->col += 2;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		else {
			if (aPiece->isBlack) {
				*outputFileStream << "Black moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 1 << " " << aPiece->col + 1 << ")." << endl;
			}
			else {
				*outputFileStream << "White moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row - 1 << " " << aPiece->col + 1 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			aPiece->row -= 1;
			aPiece->col += 1;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		break;
		// Lower left
	case 2:
		if (jump) {
			if (aPiece->isBlack) {
				*outputFileStream << "Black jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 2 << " " << aPiece->col - 2 << ")." << endl;
			}
			else {
				*outputFileStream << "White jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 2 << " " << aPiece->col - 2 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			boardLayout[(aPiece->row+1)*BOARDDIMENSIONS + (aPiece->col-1)]->isDead = true;
			boardLayout[(aPiece->row+1)*BOARDDIMENSIONS + (aPiece->col-1)] = NULL;
			aPiece->row += 2;
			aPiece->col -= 2;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		else {
			if (aPiece->isBlack) {
				*outputFileStream << "Black moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 1 << " " << aPiece->col - 1 << ")." << endl;
			}
			else {
				*outputFileStream << "White moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 1 << " " << aPiece->col - 1 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			aPiece->row += 1;
			aPiece->col -= 1;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		break;
	case 3:
		if (jump) {
			if (aPiece->isBlack) {
				*outputFileStream << "Black jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 2 << " " << aPiece->col + 2 << ")." << endl;
			}
			else {
				*outputFileStream << "White jumps from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 2 << " " << aPiece->col + 2 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			boardLayout[(aPiece->row+1)*BOARDDIMENSIONS + (aPiece->col+1)]->isDead = true;
			boardLayout[(aPiece->row+1)*BOARDDIMENSIONS + (aPiece->col+1)] = NULL;
			aPiece->row += 2;
			aPiece->col += 2;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		else {
			if (aPiece->isBlack) {
				*outputFileStream << "Black moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 1 << " " << aPiece->col + 1 << ")." << endl;
			}
			else {
				*outputFileStream << "White moves from (" << aPiece->row << " " << aPiece->col << ") to ("
						<< aPiece->row + 1 << " " << aPiece->col + 1 << ")." << endl;
			}
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = NULL;
			aPiece->row += 1;
			aPiece->col += 1;
			boardLayout[aPiece->row*BOARDDIMENSIONS + aPiece->col] = aPiece;
		}
		break;
	}

	if (aPiece->isBlack) {
		if (aPiece->row == 0) {
			*outputFileStream << "Black pawn at (" << aPiece->row << " " << aPiece->col << ") is crowned king" << endl;
			aPiece->isRoyalty = true;
		}
	}
	else {
		if (aPiece->row == 7) {
			*outputFileStream << "White pawn at (" << aPiece->row << " " << aPiece->col << ") is crowned king" << endl;
			aPiece->isRoyalty = true;
		}
	}
	writeBoardToFile();
}

int Board::canMove(Piece* aPiece, int direction) {
	int possible = 0;
	Piece* cursor = NULL;
	switch (direction) {
	// Upper left
	case 0:
		if (!aPiece->isRoyalty && !aPiece->isBlack) {
			// Possible is already set to 0
		}
		else {
			if (aPiece->col > 0 && aPiece->row > 0) {
				cursor = boardLayout[(aPiece->row-1)*BOARDDIMENSIONS + (aPiece->col-1)];
				// Test to see if there is a piece there
				if (cursor != NULL) {
					// Test for jump
					if ((aPiece->col > 1 && aPiece->row > 1) &&
							(boardLayout[(aPiece->row-2)*BOARDDIMENSIONS + (aPiece->col-2)] == NULL) &&
							((cursor->isBlack && !aPiece->isBlack) || (!cursor->isBlack && aPiece->isBlack))) {
						possible = 2;
					}
				}
				else {
					possible = 1;
				}
			}
		}
		break;

		// Upper right
	case 1:
		if (!aPiece->isRoyalty && !aPiece->isBlack) {
			// Possible is already set to 0
		}
		else {
			if (aPiece->col < 7 && aPiece->row > 0) {
				cursor = boardLayout[(aPiece->row-1)*BOARDDIMENSIONS + (aPiece->col+1)];
				// Test to see if there is a piece there
				if (cursor != NULL) {
					// Test for jump
					if ((aPiece->col < 6 && aPiece->row > 1) &&
							(boardLayout[(aPiece->row-2)*BOARDDIMENSIONS + (aPiece->col+2)] == NULL) &&
							((cursor->isBlack && !aPiece->isBlack) || (!cursor->isBlack && aPiece->isBlack))) {
						possible = 2;
					}
				}
				else {
					possible = 1;
				}
			}
		}
		break;

		// Lower left
	case 2:
		if (!aPiece->isRoyalty && aPiece->isBlack) {
			// Possible is already set to 0
		}
		else {
			if (aPiece->col > 0 && aPiece->row < 7) {
				cursor = boardLayout[(aPiece->row+1)*BOARDDIMENSIONS + (aPiece->col-1)];
				// Test to see if there is a piece there
				if (cursor != NULL) {
					// Test for jump
					if ((aPiece->col > 1 && aPiece->row < 6) &&
							(boardLayout[(aPiece->row+2)*BOARDDIMENSIONS + (aPiece->col-2)] == NULL) &&
							((cursor->isBlack && !aPiece->isBlack) || (!cursor->isBlack && aPiece->isBlack))) {
						possible = 2;
					}
				}
				else {
					possible = 1;
				}
			}
		}
		break;

		// Lower right
	case 3:
		if (!aPiece->isRoyalty && aPiece->isBlack) {
			// Possible is already set to 0
		}
		else {
			if (aPiece->col < 7 && aPiece->row < 7) {
				cursor = boardLayout[(aPiece->row+1)*BOARDDIMENSIONS + (aPiece->col+1)];
				// Test to see if there is a piece there
				if (cursor != NULL) {
					// Test for jump
					if ((aPiece->col < 6 && aPiece->row < 6) &&
							(boardLayout[(aPiece->row+2)*BOARDDIMENSIONS + (aPiece->col+2)] == NULL) &&
							((cursor->isBlack && !aPiece->isBlack) || (!cursor->isBlack && aPiece->isBlack))) {
						possible = 2;
					}
				}
				else {
					possible = 1;
				}
			}
		}
		break;

	}
	return possible;
}

bool Board::makeMove() {
	bool gameIsOver = false;
	Piece* pieceToMove = NULL;
	int directionToMove = -1;
	int moveable = 0;
	int numPossibleMoves = 0;
	if (isBlackTurn) {
		for (int i = 0; i < TOTALSTARTINGPIECES/2; i ++) {
			if (!blackPieces[i]->isDead) {
				for (int dir = 0; dir < 4; dir ++) {
					if (dir < 2 || blackPieces[i]->isRoyalty) {
						switch (moveable) {
						case 0:
							if (canMove(blackPieces[i], dir)) {
								moveable = canMove(blackPieces[i], dir);
								pieceToMove = blackPieces[i];
								directionToMove = dir;
								numPossibleMoves ++;
							}
							break;
						case 1:
							if (canMove(blackPieces[i], dir) == 2) {
								moveable = 2;
								pieceToMove = blackPieces[i];
								directionToMove = dir;
								numPossibleMoves = 1;
							}
							else if (canMove(blackPieces[i], dir) == 1) {
								if (rand() % 2) {
									pieceToMove = blackPieces[i];
									directionToMove = dir;
								}
								numPossibleMoves ++;
							}
							break;
						case 2:
							if (canMove(blackPieces[i], dir) == 2) {
								if (rand() % 2) {
									pieceToMove = blackPieces[i];
									directionToMove = dir;
								}
								numPossibleMoves ++;
							}
							break;
						}
					}
				}
			}
		}
		*outputFileStream << "Number of possible moves: " << numPossibleMoves << endl;
		switch (moveable) {
		case 0:
			*outputFileStream << "No possible moves. Black loses." << endl;
			gameIsOver = true;
			break;
		case 1:
			movePiece(pieceToMove, directionToMove, false);
			break;
		case 2:
			bool canJump = true;
			while (canJump) {
				movePiece(pieceToMove, directionToMove, true);
				moveable = 0;
				directionToMove = -1;
				for (int dir = 0; dir < 4; dir ++) {
					if (dir < 2 || pieceToMove->isRoyalty) {
						if (canMove(pieceToMove, dir) == 2) {
							if (moveable == 2) {
								if (rand() % 2) {
									directionToMove = dir;
								}
							}
							else {
								directionToMove = dir;
								moveable = 2;
							}
						}
					}
				}
				if (moveable != 2) {
					canJump = false;
				}
			}
			break;
		}
	}
	else {
		for (int i = 0; i < TOTALSTARTINGPIECES/2; i ++) {
			if (!whitePieces[i]->isDead) {
				for (int dir = 0; dir < 4; dir ++) {
					if (dir > 1 || whitePieces[i]->isRoyalty) {
						switch (moveable) {
						case 0:
							if (canMove(whitePieces[i], dir)) {
								moveable = canMove(whitePieces[i], dir);
								pieceToMove = whitePieces[i];
								directionToMove = dir;
								numPossibleMoves ++;
							}
							break;
						case 1:
							if (canMove(whitePieces[i], dir) == 2) {
								moveable = 2;
								pieceToMove = whitePieces[i];
								directionToMove = dir;
								numPossibleMoves = 1;
							}
							else if (canMove(whitePieces[i], dir) == 1) {
								if (rand() % 2) {
									pieceToMove = whitePieces[i];
									directionToMove = dir;
								}
								numPossibleMoves ++;
							}
							break;
						case 2:
							if (canMove(whitePieces[i], dir) == 2) {
								if (rand() % 2) {
									pieceToMove = whitePieces[i];
									directionToMove = dir;
								}
								numPossibleMoves ++;
							}
							break;
						}
					}
				}
			}
		}
		*outputFileStream << "Number of possible moves: " << numPossibleMoves << endl;
		switch (moveable) {
		case 0:
			*outputFileStream << "No possible moves. White loses." << endl;
			gameIsOver = true;
			break;
		case 1:
			movePiece(pieceToMove, directionToMove, false);
			break;
		case 2:
			bool canJump = true;
			while (canJump) {
				movePiece(pieceToMove, directionToMove, true);
				moveable = 0;
				directionToMove = -1;
				for (int dir = 0; dir < 4; dir ++) {
					if (dir > 1 || pieceToMove->isRoyalty) {
						if (canMove(pieceToMove, dir) == 2) {
							if (moveable == 2) {
								if (rand() % 2) {
									directionToMove = dir;
								}
							}
							else {
								directionToMove = dir;
								moveable = 2;
							}
						}
					}
				}
				if (moveable != 2) {
					canJump = false;
				}
			}
			break;
		}
	}
	isBlackTurn = !isBlackTurn;
	return gameIsOver;
}

void Board::displayBoardToConsole() {
	int i = 0;
	while (i < 8) {
		writeBorderToFile(&cout);
		writeEmptyPartOfRowToFile(&cout);
		writeRowContentToFile(i, &cout);
		writeEmptyPartOfRowToFile(&cout);
		i ++;
	}
	writeBorderToFile(&cout);
}

