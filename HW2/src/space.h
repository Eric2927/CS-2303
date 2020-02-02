/*
 * space.h
 *
 *  Created on: Jan 27, 2020
 *      Author: Therese
 */

#ifndef SPACE_H_
#define SPACE_H_

#include <stdbool.h>
#include "marker.h"
bool initSpace(int*, int);
void displaySpace(int*, int);
Marker* generateRandomStart(int* corner, int howManyRows);
Marker* generateNextPosition(int* corner, int howManyRows, Marker* prevMarker);

#endif /* SPACE_H_ */
