/*
 * marker.c
 *
 *  Created on: Jan 27, 2020
 *      Author: Therese
 */

#include "marker.h"

Marker* placeMarker(int r, int c, int i)
{
	Marker* mP = (Marker*) malloc (sizeof(Marker));
	//TODO what do we do?
	mP->row = r;
	mP->col = c;
	mP->index = i;

	return mP;
}
