/*
 * Production.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "EL.h"
#include "Board.h"
#include "Ship.h"

class Production {
public:
	Production();
	virtual ~Production();
	bool prod(int argc, char* argv[]);
};

#endif /* PRODUCTION_H_ */
