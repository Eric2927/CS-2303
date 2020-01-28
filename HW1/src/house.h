/*
 * house.h
 *
 *  Created on: Jan 28, 2020
 *      Author: eric_li
 */

#ifndef HOUSE_H_
#define HOUSE_H_

#include <stdbool.h>;

int countRooms(Layout aLayout);
Room getFirstRoom(Layout aLayout);

typedef struct {
	Room aRoom;
} House;


#endif /* HOUSE_H_ */
