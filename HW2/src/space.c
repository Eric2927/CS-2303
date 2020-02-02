/*
 * space.c
 *
 *  Created on: Jan 27, 2020
 *      Author: Therese
 */
#include "space.h"

// Assumes square
bool initSpace(int* corner, int howManyRows)
{
	bool ok = true;
	for(int row = 0; row < howManyRows; row++)
	{
		for(int col = 0; col < howManyRows; col++)
		{
			*(corner+row*howManyRows + col) = 0;
		}
	}
	return ok;
}

Marker* generateRandomStart(int* corner, int howManyRows) {
	int randomRow = rand() % howManyRows;
	int randomCol = rand() % howManyRows;
	*(corner+randomRow*howManyRows + randomCol) = 1;
	return placeMarker(randomRow, randomCol, 1);
}

Marker* generateNextPosition(int* corner, int howManyRows, Marker* prevMarker) {
	int whereToGoNext;
	int newRow = prevMarker->row;
	int newCol = prevMarker->col;
	bool valid = false;
	while (!valid) {
		whereToGoNext = rand() % 4;
		switch (whereToGoNext) {
		case 0:
			if (prevMarker->col != 0) {
				newCol --;
				valid = true;
			}
			break;
		case 1:
			if (prevMarker->row != 0) {
				newRow --;
				valid = true;
			}
			break;
		case 2:
			if (prevMarker->col != howManyRows - 1) {
				newCol ++;
				valid = true;
			}
			break;
		case 3:
			if (prevMarker->row != howManyRows - 1) {
				newRow ++;
				valid = true;
			}
		}
	}

	for (int row = 0; row < howManyRows; row++)
	{
		for(int col = 0; col < howManyRows; col++)
		{
			*(corner+row*howManyRows + col) = 0;
		}
	}

	*(corner + newRow*howManyRows + newCol) = prevMarker->index + 1;
	return placeMarker(newRow, newCol, prevMarker->index + 1);
}


void displaySpace(int* corner, int howManyRows) {
	for(int row = 0; row < howManyRows; row++)
	{
		for(int col = 0; col < howManyRows; col++)
		{
			printf("%d\t",*(corner+row*howManyRows + col));
		}
		puts("\n");
	}
}
