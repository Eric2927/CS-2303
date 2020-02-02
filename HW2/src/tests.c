/*
 * tests.c
 *
 *  Created on: Jul 4, 2019
 *      Author: Therese
 */

#include "tests.h"
#include "production.h"
#include "EL.h"


bool tests()
{
	srand(time(0));
	bool answer = false;
	answer = testInitSpace() && testGenerateRandomStart() && testGenerateNextPosition();
	return answer;
}

bool testInitSpace() {
	bool success = true;
	int* theSpaceP = (int*) malloc(5*5*sizeof(int));
    initSpace(theSpaceP, 5);

    // Makes sure that all integers in the allocated memory for theSpaceP is 0
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (*(theSpaceP+row*5 + col) != 0) {
				success = false;
			}
		}
	}
	if (success) {
		puts("Passed testInitSpace");
	}
	else {
		puts("Failed testInitSpace");
	}
    return success;
}

bool testGenerateRandomStart() {
	bool success = true;
	int* theSpaceP = (int*) malloc(5*5*sizeof(int));
    initSpace(theSpaceP, 5);
    Marker* randomMarker = generateRandomStart(theSpaceP, 5);

    // First checks if the randomMarker has index 1
    if (randomMarker->index == 1) {

    	// Now checks if the grid (theSpaceP) was updated correctly
    	for(int row = 0; row < 5; row++)
    	{
    		for(int col = 0; col < 5; col++)
    		{
    			if (row == randomMarker->row && col == randomMarker->col) {
    				if (*(theSpaceP + randomMarker->row*5 + randomMarker->col) != 1) {
    					success = false;
    				}
    			}
    			else if (*(theSpaceP+row*5 + col) != 0) {
    				success = false;
    			}
    		}
    	}
    }
    else {
    	success = false;
    }
	if (success) {
		puts("Passed testGenerateRandomStart");
	}
	else {
		puts("Failed testGenerateRandomStart");
	}
    return success;
}

bool testGenerateNextPosition() {
	bool success = true;
	int* theSpaceP = (int*) malloc(5*5*sizeof(int));
    initSpace(theSpaceP, 5);
    Marker* topBorder = placeMarker(0, 3, 2);
    Marker* leftBorder = placeMarker(3, 0, 2);
    Marker* bottomBorder = placeMarker(4, 1, 2);
    Marker* rightBorder = placeMarker(1, 4, 2);

    // Test 50 times to see if the next random position is out of bounds
    int numTests = 50;
    while (numTests < 50) {
    	Marker* newMarker = generateNextPosition(theSpaceP, 5, topBorder);
    	if (newMarker->row < 0) {
    		success = false;
    	}
    	newMarker = generateNextPosition(theSpaceP, 5, leftBorder);
    	if (newMarker->col < 0) {
    		success = false;
    	}
    	newMarker = generateNextPosition(theSpaceP, 5, bottomBorder);
    	if (newMarker->row >= 5) {
    		success = false;
    	}
    	newMarker = generateNextPosition(theSpaceP, 5, rightBorder);
    	if (newMarker->col >= 5) {
    		success = false;
    	}
    }

    int* theSpaceP2 = (int*) malloc(5*5*sizeof(int));
    initSpace(theSpaceP2, 5);
    Marker* position1 = generateRandomStart(theSpaceP2, 5);
    Marker* position2 = generateNextPosition(theSpaceP2, 5, position1);

    // Tests to make sure theSpaceP2 is properly updated
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (row == position2->row && col == position2->col) {
				if (*(theSpaceP2+row*5 + col) != 2) {
					success = false;
				}
			}
			else if (*(theSpaceP2+row*5 + col) != 0) {
				success = false;
			}
		}
	}

	// Tests once more to make sure theSpaceP2 is properly updated after a second move
    Marker* position3 = generateNextPosition(theSpaceP2, 5, position2);
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (row == position3->row && col == position3->col) {
				if (*(theSpaceP2+row*5 + col) != 3) {
					success = false;
				}
			}
			else if (*(theSpaceP2+row*5 + col) != 0) {
				success = false;
			}
		}
	}
	if (success) {
		puts("Passed testGenerateNextPosition");
	}
	else {
		puts("Failed testGenerateNextPosition");
	}
	return success;
}

