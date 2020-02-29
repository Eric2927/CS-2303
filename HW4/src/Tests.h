/*
 * Tests.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef TESTS_H_
#define TESTS_H_

#include "EL.h"
#include "production.h"

class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();
	bool testReadFile();
	bool testGotAdjacencyMatrix();
	bool testMakeLList();
	bool testEnqueue();
	bool testWriteHistory();
};

#endif /* TESTS_H_ */
