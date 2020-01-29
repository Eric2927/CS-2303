/*
 * layout.c
 *
 *  Created on: Jan 28, 2020
 *      Author: eric_li
 */

#include "layout.h"

int nRooms = 0; // arbitrary number

int countRooms() {
	return nRooms;
}

Room getFirstRoom() {
	Room firstRoom = {false, true};	// arbitrary arguments
	open(firstRoom);
	return firstRoom;
}
