/*
 * room.c
 *
 *  Created on: Jan 28, 2020
 *      Author: eric_li
 */

#include "room.h"

bool open(Room aRoom) {
	aRoom.open = true;
	return true;
}

bool haveTreasure(Room aRoom) {
	return aRoom.treasure;
}

