/*
 * room.h
 *
 *  Created on: Jan 28, 2020
 *      Author: eric_li
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <stdbool.h>;

typedef struct {
	bool open;
	bool treasure;
} Room;

bool open(Room aRoom);
bool haveTreasure(Room aRoom);

#endif /* ROOM_H_ */
