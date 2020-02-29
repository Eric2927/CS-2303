/*
 * Tests.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Tests.h"
#include <stdbool.h>

using namespace std;

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests()
{
	bool answer = false;
	bool ok1 = this->testReadFile();
	bool ok2 = this->testGotAdjacencyMatrix();
	bool ok3 = this->testMakeLList();
	bool ok4 = this->testEnqueue();
	bool ok5 = this->testWriteHistory();
	answer = ok1 && ok2 && ok3 && ok4 && ok5;
	return answer;
}

bool Tests::testReadFile() {
	cout << "Starting testReadFile" << endl;
	bool ok = false;
	Production* pP = new Production();
	//the file tells how many rooms there are
	int answer = -1;
	int rightAnswer = 8;

	AdjMat* adjMP = new AdjMat();
	Room* theRoomPs[10];//addresses for 10 rooms

	ok = pP->readFile("houseGraph.txt", &answer, adjMP, theRoomPs); //read the file
	if (ok)
	{
		if (answer!=rightAnswer)
		{
			puts("test failed on number of rooms");
			ok = false;
		}

	}
	puts("The adjacency matrix");
	for(int i = 0; i<answer; i++)
	{
		for(int j = 0; j<answer; j++)
		{
			printf("%d",adjMP->getEdge(i, j));

		}
		printf("\n");
	}
	puts("The treasure values");
	for(int i = 0; i<answer; i++)
	{
		printf("%f\n", theRoomPs[i]->treasure);
	}

	//fclose();
	return ok;
}

bool Tests::testGotAdjacencyMatrix() {
	bool ans = true;
	cout << "starting testGotAdjacencyMatrix" << endl;

	// test case 1: init
	AdjMat* adjMP = new AdjMat();
	adjMP->init(5);
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (adjMP->getEdge(row, col) != 0) {
				ans = false;
			}
		}
	}

	// test case 2: setEdge and getEdge
	adjMP->setEdge(1, 4);
	adjMP->setEdge(3, 2);
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (row == 1 && col == 4) {
				if (adjMP->getEdge(row, col) != 1) {
					ans = false;
				}
			}
			else if (row == 4 && col == 1) {
				if (adjMP->getEdge(row, col) != 1) {
					ans = false;
				}
			}
			else if (row == 3 && col == 2) {
				if (adjMP->getEdge(row, col) != 1) {
					ans = false;
				}
			}
			else if (row == 2 && col == 3) {
				if (adjMP->getEdge(row, col) != 1) {
					ans = false;
				}
			}
			else {
				if (adjMP->getEdge(row, col) != 0) {
					ans = false;
				}
			}
		}
	}

	if (ans) {
		puts("testGotAdjacencyMatrix passed.");
	}
	else {
		puts("testGotAdjacencyMatrix did not pass.");
	}
	return ans;
}

bool Tests::testMakeLList() {
	bool ok = true;
	cout << "Starting testMakeLList" << endl;
	//what are the criteria for success for make LList?
	//should be able to make one, add data to it, get the data back
	//test case 1:
	LinkedList<Room>* theListP = new LinkedList<Room>();
	bool rightAnswer = true;
	bool answer = theListP->isEmpty();
	if(answer!=rightAnswer)
	{
		ok = false;
	}
	//test case 2:
	Room* roomOne = new Room();
	roomOne->roomNumber = 46;
	roomOne->searched = true;
	roomOne->treasure = 3.2;
	theListP->savePayload(roomOne);
	if (theListP->isEmpty()) {
		ok = false;
	}

	// test case 3:
	if (theListP->dequeueLIFO() != roomOne) {
		ok = false;
	}

	if (ok) {
		puts("test make LList passed.");
	}
	else {
		puts("test make LList did not pass.");
	}

	return ok;
}

bool Tests::testEnqueue() {
	bool works = true;
	LinkedList<Room>* theListP = new LinkedList<Room>();

	// test case 1: dequeueLIFO
	Room* roomOne = new Room();
	Room* roomTwo = new Room();
	Room* roomThree = new Room();
	roomOne->roomNumber = 1;
	roomTwo->roomNumber = 2;
	roomThree->roomNumber = 3;
	theListP->savePayload(roomOne);
	theListP->savePayload(roomTwo);
	theListP->savePayload(roomThree);
	if (theListP->dequeueLIFO() != roomThree) {
		works = false;
	}
	if (theListP->dequeueLIFO() != roomTwo) {
		works = false;
	}
	if (theListP->dequeueLIFO() != roomOne) {
		works = false;
	}

	// test case 2: dequeueFIFO
	LinkedList<SearchResults>* theListP2 = new LinkedList<SearchResults>();
	SearchResults* resultOne = new SearchResults();
	SearchResults* resultTwo = new SearchResults();
	theListP2->savePayload(resultOne);
	theListP2->savePayload(resultTwo);
	if (theListP2->dequeueFIFO() != resultOne) {
		works = false;
	}
	if (theListP2->dequeueFIFO() != resultTwo) {
		works = false;
	}

	if (works) {
		puts("testEnqueue passed.");
	}
	else {
		puts("testEnqueue did not pass.");
	}

	return works;
}

bool Tests::testWriteHistory() {
	bool works = true;
	char* outputFilename = "outputFile.txt";
	LinkedList<SearchResults>* theListP = new LinkedList<SearchResults>();
	SearchResults* resultOne = new SearchResults();
	SearchResults* resultTwo = new SearchResults();
	SearchResults* resultThree = new SearchResults();
	resultOne->roomNumber = 17;
	resultTwo->roomNumber = 24;
	resultThree->roomNumber = 37;
	resultOne->treasure = 105.5;
	resultTwo->treasure = 213.7;
	resultThree->treasure = 12.1;
	theListP->savePayload(resultOne);
	theListP->savePayload(resultTwo);
	theListP->savePayload(resultThree);
	theListP->writeHistory(outputFilename);
	ifstream inFile;
	inFile.open(outputFilename);
	int actualRoomNumber = -1;
	float actualTreasure = -1;
	int roomCounter = 1;
	while (!inFile.eof()) {
		inFile >> actualRoomNumber;
		inFile >> actualTreasure;
		switch (roomCounter) {
		case 1:
			if (actualRoomNumber != resultOne->roomNumber) {
				works = false;
			}
			if (actualTreasure != resultOne->treasure) {
				works = false;
			}
			break;
		case 2:
			if (actualRoomNumber != resultTwo->roomNumber) {
				works = false;
			}
			if (actualTreasure > resultOne->treasure + resultTwo->treasure + 0.1
					|| actualTreasure < resultOne->treasure + resultTwo->treasure - 0.1) {
				works = false;
			}
			break;
		case 3:
			if (actualRoomNumber != resultThree->roomNumber) {
				works = false;
			}
			if (actualTreasure > resultOne->treasure + resultTwo->treasure + resultThree->treasure + 0.1
					|| actualTreasure < resultOne->treasure + resultTwo->treasure + resultThree->treasure - 0.1) {
				works = false;
			}
			break;
		default:
			cout << "Extra information at end of file" << endl;
			works = false;
		}
		roomCounter ++;
	}
	if (works) {
		cout << "testWriteHistory passed" << endl;
	}
	else {
		cout << "testWriteHistory did not pass" << endl;
	}

	return works;
}
