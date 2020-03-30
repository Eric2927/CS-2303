/*
 * Ship.cpp
 *
 *  Created on: Mar 2, 2020
 *      Author: eric_li
 */

#include "Ship.h"

Ship::Ship(int typeOfShip) {
	numHits = 0;
	switch (typeOfShip) {
	// Carrier
	case 0:
		name = "Carrier";
		length = 5;
		symbol = 'c';
		break;
	case 1:
	// Battleship
		name = "Battleship";
		length = 4;
		symbol = 'b';
		break;
	// Cruiser
	case 2:
		name = "Cruiser";
		length = 3;
		symbol = 'r';
		break;
	case 3:
	// Submarine
		name = "Submarine";
		length = 3;
		symbol = 's';
		break;
	// Destroyer
	case 4:
		name = "Destroyer";
		length = 2;
		symbol = 'd';
		break;
	}
}

Ship::~Ship() {
}

char* Ship::getName() {
	return name;
}

int Ship::getLength() {
	return length;
}

char Ship::getSymbol() {
	return symbol;
}

void Ship::hit() {
	numHits ++;
}

bool Ship::isSunk() {
	return numHits >= length;
}





