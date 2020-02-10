/*
 * tests.c
 *
 *  Created on: Jul 4, 2019
 *      Author: Therese
 */

#include "tests.h"
#include "production.h"
#include "LinkedList.h"


bool tests()
{
	bool answer = false;
	bool ok1 = testReadFile();
	bool ok2 = testGotAdjacencyMatrix();
	bool ok3 = testMakeLList();
	bool ok4 = testEnqueue();
	bool ok5 = testRemoveFromList();
	bool ok6 = testPrintHistory();
	answer = ok1 && ok2 && ok3 && ok4 && ok5 && ok6;
	return answer;
}

bool testReadFile()
{
	puts("starting testReadFile"); fflush(stdout);
	bool ok = false;
	//the file tells how many rooms there are
	int answer = -1;
	int rightAnswer = 8;


	AdjMat* adjMP = (AdjMat*) malloc(sizeof(AdjMat));
	Room* theRoomPs[10];//addresses for 10 rooms


	ok = readFile("houseGraph.txt", &answer, adjMP, theRoomPs); //read the file
	if(ok)
	{
		if(answer!=rightAnswer)
		{
			puts("test failed on number of rooms");
		}

	}
	puts("The adjacency matrix");
	for(int i = 0; i<answer; i++)
	{
		for(int j = 0; j<answer; j++)
		{
			printf("%d",getEdge(adjMP, i, j));

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

bool testGotAdjacencyMatrix()
{
	bool ans = true;
	puts("starting testGotAdjacencyMatrix");

	// test case 1: init
	AdjMat* adjMP = (AdjMat*) malloc(sizeof(AdjMat));
	adjMP->n = 5;
	adjMP->edgesP = (int*) malloc(5*5*sizeof(int));
	init(adjMP);
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (*((adjMP->edgesP)+(row*5)+col) != 0) {
				ans = false;
			}
		}
	}

	// test case 2: setEdge
	setEdge(adjMP, 1, 4);
	setEdge(adjMP, 3, 2);
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (row == 1 && col == 4) {
				if (*((adjMP->edgesP)+(row*5)+col) != 1) {
					ans = false;
				}
			}
			else if (row == 4 && col == 1) {
				if (*((adjMP->edgesP)+(row*5)+col) != 1) {
					ans = false;
				}
			}
			else if (row == 3 && col == 2) {
				if (*((adjMP->edgesP)+(row*5)+col) != 1) {
					ans = false;
				}
			}
			else if (row == 2 && col == 3) {
				if (*((adjMP->edgesP)+(row*5)+col) != 1) {
					ans = false;
				}
			}
			else {
				if (*((adjMP->edgesP)+(row*5)+col) != 0) {
					ans = false;
				}
			}
		}
	}

	// test case 3: getEdge
	for(int row = 0; row < 5; row++)
	{
		for(int col = 0; col < 5; col++)
		{
			if (row == 1 && col == 4) {
				if (getEdge(adjMP, row, col) != 1) {
					ans = false;
				}
			}
			else if (row == 4 && col == 1) {
				if (getEdge(adjMP, row, col) != 1) {
					ans = false;
				}
			}
			else if (row == 3 && col == 2) {
				if (getEdge(adjMP, row, col) != 1) {
					ans = false;
				}
			}
			else if (row == 2 && col == 3) {
				if (getEdge(adjMP, row, col) != 1) {
					ans = false;
				}
			}
			else {
				if (getEdge(adjMP, row, col) != 0) {
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

bool testMakeLList()
{
	bool ok = true;
	puts("starting testMakeLList");fflush(stdout);
	//what are the criteria for success for make LList?
	//should be able to make one, add data to it, get the data back
	//test case 1:
	LLNode* theListP = makeEmptyLinkedList();
	bool rightAnswer = true;
	bool answer = isEmpty(theListP);
	if(answer!=rightAnswer)
	{
		ok = false;
	}
	//test case 2:
	Room* roomOne = (Room*) malloc(sizeof(Room));
	roomOne->roomNumber = 46;
	roomOne->searched = true;
	roomOne->treasure = 3.2;
	savePayload(theListP, roomOne);
	if (isEmpty(theListP)) {
		ok = false;
	}

	// test case 3:
	if (theListP->payP->roomNumber != 46 &&
			theListP->payP->searched != true &&
			theListP->payP->treasure != 3.2) {
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

// Since there is no official "enqueue" function besides savePayload,
// which has already been tested in testMakeLList,
// this test will be testing the two dequeue functions instead
bool testEnqueue() {
	bool works = true;
	LLNode* theListP = makeEmptyLinkedList();

	// test case 1: dequeueLIFO
	Room* roomOne = (Room*) malloc(sizeof(Room));
	Room* roomTwo = (Room*) malloc(sizeof(Room));
	Room* roomThree = (Room*) malloc(sizeof(Room));
	Room* roomFour = (Room*) malloc(sizeof(Room));
	roomOne->roomNumber = 1;
	roomTwo->roomNumber = 2;
	roomThree->roomNumber = 3;
	roomFour->roomNumber = 4;
	savePayload(theListP, roomOne);
	savePayload(theListP, roomTwo);
	savePayload(theListP, roomThree);
	if (dequeueLIFO(theListP) != roomThree) {
		works = false;
	}
	if (dequeueLIFO(theListP) != roomTwo) {
		works = false;
	}

	// test case 2: dequeueFIFO
	savePayload(theListP, roomThree);
	savePayload(theListP, roomFour);
	backFromDQFIFO* dqFirst = dequeueFIFO(theListP);
	if (dqFirst->mp != roomOne) {
		works = false;
	}
	theListP = dqFirst->newQHead;
	backFromDQFIFO* dqSecond = dequeueFIFO(theListP);
	if (dqSecond->mp != roomThree) {
		works = false;
	}
	if (dqSecond->newQHead->payP != roomFour) {
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



bool testRemoveFromList()
{
	bool ok = true;
	//cases:
	//1 list is empty:return same list
	//2 list is of length one, and item is present: return empty list
	//3 list is of length one, and item is not present: return same list
	//4 list is longer than one, item is present, at first location: return list starting at second element
	//5 list is longer than one, item is present, not at first location: return list with item removed
	//6 list is longer than one, item is not present: return same list
	LLNode* case1 = makeEmptyLinkedList();
	Payload* pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	LLNode* ans = removeFromList(case1, pay1);
	if((ans != case1) || (ans->payP != (Payload*)0))
	{
		ok = false;

	}
	printf("testRemove case 1 with %d\n", ok); fflush(stdout);
	savePayload(case1, pay1);
	//this is case2
	ans = removeFromList(case1, pay1);
	if((ans != case1) || (ans->payP != (Payload*)0))
	{
		ok = false;

	}
	printf("testRemove case 2 with %d\n", ok); fflush(stdout);
	//now case 3
	Payload* pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	ans = removeFromList(case1, pay3);
	if(ans != case1)//this is only a partial check for list unchanged
	{
		ok = false;

	}
	printf("testRemove case 3 with %d\n", ok); fflush(stdout);
	//now case 4
	case1 = makeEmptyLinkedList();
	pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	savePayload(case1, pay1);
	pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	savePayload(case1, pay3);
	ans = removeFromList(case1, pay1);

	if(ans == case1)
	{
		ok = false;

	}
	printf("testRemove case 4 with %d\n", ok); fflush(stdout);
	//now case 5
	case1 = makeEmptyLinkedList();
	pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	savePayload(case1, pay1);
	pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	savePayload(case1, pay3);
	//puts("trying case 5");fflush(stdout);
	ans = removeFromList(case1, pay3);//ans should be equal to case1
	LLNode* theNext = (LLNode*) ans->next; //this is element where pay3 got attached
	Payload* check = (Payload*) 0;
	if (theNext)
	{
		check = theNext->payP; //this should be pay3, which should have been removed
	}
	//printf("testRemove returned from case 5\n"); fflush(stdout);
	if((ans != case1) || (check != (Payload*)0))//disquiet
	{
		ok = false;

	}
	//printf("ans == case1 is %d\n", ans==case1);
	//printf("check != 0 is %d\n", check != (Payload*)0);
	printf("testRemove case 5 with %d\n", ok); fflush(stdout);
	//now case 6
	case1 = makeEmptyLinkedList();
	pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	savePayload(case1, pay1);
	pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	savePayload(case1, pay3);
	Payload* another = (Payload*) malloc(sizeof(Room));
	another->roomNumber=2;
	ans = removeFromList(case1, another);
	if((ans != case1))
	{
		ok = false;

	}
	printf("testRemove case 6 with %d\n", ok); fflush(stdout);
	return ok;
}

// Not sure how this can be tested, since printHistory only prints out strings and doesn't return anything
// Therefore, this test will be purely visual, based on reading the console.
bool testPrintHistory()
{
	bool ok = true;
	puts("Starting testPrintHistory");
	LLNode* theListP = makeEmptyLinkedList();
	puts("\nCorrect Result 1:\n\"Empty List\"\nActual Result:");
	printHistory(theListP); // Should print "Empty List"
	Room* roomOne = (Room*) malloc(sizeof(Room));
	Room* roomNine = (Room*) malloc(sizeof(Room));
	Room* roomThirteen = (Room*) malloc(sizeof(Room));
	roomOne->roomNumber = 1;
	roomOne->treasure = 3.1;
	roomNine->roomNumber = 9;
	roomNine->treasure = 2.4;
	roomThirteen->roomNumber = 13;
	roomThirteen->treasure = 20.5;
	savePayload(theListP, roomOne);
	savePayload(theListP, roomNine);
	savePayload(theListP, roomThirteen);
	puts("\nCorrect Result 2:\n\"The room was 1, and the treasure subtotal was 3.1\n"
			"The room was 9, and the treasure subtotal was 5.5\n"
			"The room was 13, and the treasure subtotal was 26\"\nActual Result:");
	printHistory(theListP);
	puts("");
	return ok;
}
