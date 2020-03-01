/*
 * Board.h
 *
 *  Created on: Feb 29, 2020
 *      Author: eric_li
 */

#ifndef BOARD_H_
#define BOARD_H_

struct Piece {
	bool isRoyalty;
	bool isUserOne;
	bool isDespacito;
	int x;
	int y;
};

class Board {
private:
	Piece* activePieces;
	bool isUserOneTurn;
public:
	Board();
	virtual ~Board();
	void displayBoard();
	void makeMove();
	bool movePiece(Piece* aPiece);
	int isGameOver();
};

#endif /* BOARD_H_ */
