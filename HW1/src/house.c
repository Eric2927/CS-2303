/*
 * house.c
 *
 *  Created on: Jan 28, 2020
 *      Author: eric_li
 */

#include "house.h"

int getNumberOfRooms() {
	int nRooms = countRooms();
	return nRooms;
}

Room getNewRoom() {
	Room firstRoom = getFirstRoom();
	return firstRoom;
}
