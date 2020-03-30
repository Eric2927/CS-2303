/*
 * Ship.h
 *
 *  Created on: Mar 2, 2020
 *      Author: eric_li
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "EL.h"

class Ship {
private:
	char* name;
	int length;
	char symbol;
	int numHits;
public:
	Ship(int typeOfShip);
	virtual ~Ship();
	char* getName();
	int getLength();
	char getSymbol();
	void hit();
	bool isSunk();
	friend class Tests;
};

#endif /* SHIP_H_ */
