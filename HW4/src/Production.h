/*
 * Production.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "EL.h"

class Production {
private:
	const int FILENAMELENGTHALLOWANCE = 50;
public:
	Production();
	virtual ~Production();
	bool prod(int argc, char* argv[]);
	bool readFile(char* filename, int* nrooms, AdjMat* adjMP, Room** theRoomPs);
	void displayBoard();
};

#endif /* PRODUCTION_H_ */
