/*
 * layout.h
 *
 *  Created on: Jan 28, 2020
 *      Author: eric_li
 */

#ifndef LAYOUT_H_
#define LAYOUT_H_

#include <stdbool.h>;

bool open(Room aRoom);

typedef struct {
	int nRooms;
	Room firstRoom;
} Layout;



#endif /* LAYOUT_H_ */
