/*
 * LinkedList.cpp
 *
 *  Created on: Feb 23, 2020
 *      Author: eric_li
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

template <> LinkedList<Payload1>::LinkedList() {
	head = new LLNode();
	head->next = (LLNode*) 0;
	head->prev = (LLNode*) 0;
	head->payP = (Payload1*) 0;
}

template <> LinkedList<Payload2>::LinkedList() {
	head = new LLNode();
	head->next = (LLNode*) 0;
	head->prev = (LLNode*) 0;
	head->payP = (Payload2*) 0;
}

template <> LinkedList<Payload1>::~LinkedList() {
	LLNode* cursor = head;
	while (cursor->next) {
		LLNode* prev = cursor;
		cursor = cursor->next;
		prev->next = (LLNode*) 0;
		prev->prev = (LLNode*) 0;
		delete prev->payP;
		delete prev;
	}
	cursor->prev = (LLNode*) 0;
	delete cursor->payP;
	delete cursor;
}

template <> LinkedList<Payload2>::~LinkedList() {
	LLNode* cursor = head;
	while (cursor->next) {
		LLNode* prev = cursor;
		cursor = cursor->next;
		prev->next = (LLNode*) 0;
		prev->prev = (LLNode*) 0;
		delete prev->payP;
		delete prev;
	}
	cursor->prev = (LLNode*) 0;
	delete cursor->payP;
	delete cursor;
}

template <> void LinkedList<Payload1>::removeFromList(Payload1* pP) {
	//find the payload
	//use the structure of a list, namely, list is empty or element followed by list
	if (!this->isEmpty())
	{
		//puts("list is not empty");fflush(stdout);
		LLNode* altHead = (LLNode*)head->next;
		//find the item, if it is there
		LLNode* temp = head;
		bool done = false;
		while((!done) && temp->next)
		{
			//are we there yet?
			if(temp->payP == pP)
			{
				done=true;
				//puts("found it 1");fflush(stdout);
			}
			else
			{
				temp=(LLNode*)temp->next;
			}
		}
		//either we are pointing to the correct element, or we are at the end, or both
		if((temp->payP) == pP)
		{
			//puts("found it 2");fflush(stdout);
			//found it, remove it
			//are we at the beginning?
			if(temp == head)
			{  //found it at the first element
				//puts("found it at first element");fflush(stdout);
				//is the list of length 1?
				if(!(temp->next))
				{//if there is no next
					//remove payload, return empty list
					head->payP = (Payload1*)0;
				}
				else //not of length 1
				{ //not freeing the Payload, but freeing the first list element
					//puts("found it at first element of list with length > 1");fflush(stdout);
					//free(hP);
					head = altHead;
				}
			}
			else //not found at first location in list
			{
				//puts("found it not at first element");fflush(stdout);
				//save the linkages
				//found element has a next
				//found element has a prev
				//participant before has a next
				//participant after has a prev
				LLNode* prevPart = (LLNode*) temp->prev;//non-zero because not at first element
				LLNode* nextPart = (LLNode*) temp->next;//could be zero, if found at last element
				prevPart->next = (LLNode*) nextPart;//RHS is 0 if at end
				//puts("after setting the next of the previous");fflush(stdout);
				// printf("Next is %p, %d\n", nextPart, (bool)nextPart);fflush(stdout);
				if((bool)nextPart)//don't need guarded block if element found at end of list
				{
					//puts("before setting the previous of the next");fflush(stdout);
					nextPart->prev = (LLNode*) prevPart;

				}
				//puts("after handling the  previous of the next");fflush(stdout);
			}//end of not found at first location
		}//end of found it
		else
		{
			//didn't find it
			//puts("did not find it");fflush(stdout);
			//nothing to do
		}//end did not find it
	}
	//printf("Returning %p\n", retHead); fflush(stdout);
}

template <> void LinkedList<Payload2>::removeFromList(Payload2* pP) {
	//find the payload
	//use the structure of a list, namely, list is empty or element followed by list
	if (!this->isEmpty())
	{
		//puts("list is not empty");fflush(stdout);
		LLNode* altHead = (LLNode*)head->next;
		//find the item, if it is there
		LLNode* temp = head;
		bool done = false;
		while((!done) && temp->next)
		{
			//are we there yet?
			if(temp->payP == pP)
			{
				done=true;
				//puts("found it 1");fflush(stdout);
			}
			else
			{
				temp=(LLNode*)temp->next;
			}
		}
		//either we are pointing to the correct element, or we are at the end, or both
		if((temp->payP) == pP)
		{
			//puts("found it 2");fflush(stdout);
			//found it, remove it
			//are we at the beginning?
			if(temp == head)
			{  //found it at the first element
				//puts("found it at first element");fflush(stdout);
				//is the list of length 1?
				if(!(temp->next))
				{//if there is no next
					//remove payload, return empty list
					head->payP = (Payload2*)0;
				}
				else //not of length 1
				{ //not freeing the Payload, but freeing the first list element
					//puts("found it at first element of list with length > 1");fflush(stdout);
					//free(hP);
					head = altHead;
				}
			}
			else //not found at first location in list
			{
				//puts("found it not at first element");fflush(stdout);
				//save the linkages
				//found element has a next
				//found element has a prev
				//participant before has a next
				//participant after has a prev
				LLNode* prevPart = (LLNode*) temp->prev;//non-zero because not at first element
				LLNode* nextPart = (LLNode*) temp->next;//could be zero, if found at last element
				prevPart->next = (LLNode*) nextPart;//RHS is 0 if at end
				//puts("after setting the next of the previous");fflush(stdout);
				// printf("Next is %p, %d\n", nextPart, (bool)nextPart);fflush(stdout);
				if((bool)nextPart)//don't need guarded block if element found at end of list
				{
					//puts("before setting the previous of the next");fflush(stdout);
					nextPart->prev = (LLNode*) prevPart;

				}
				//puts("after handling the  previous of the next");fflush(stdout);
			}//end of not found at first location
		}//end of found it
		else
		{
			//didn't find it
			//puts("did not find it");fflush(stdout);
			//nothing to do
		}//end did not find it
	}
	//printf("Returning %p\n", retHead); fflush(stdout);
}

template <> void LinkedList<Payload1>::savePayload(Payload1* mp) {
	//if the list is empty, then make payP be mp
	//else traverse the list,
	//make a new list element
	//put mp in that
	//attach the new list element to the existing list
	if(this->isEmpty())
	{
		head->payP = mp;
	}
	else
	{
		LLNode* cursor = head;
		while(cursor->next)
		{
			cursor=(LLNode*)cursor->next;
		}
		//now temp points to the last element

		//make a new element, attach mp to it, wire up the new element
		LLNode* newNode = new LLNode();
		newNode->payP = (Payload1*) mp;
		cursor->next = (LLNode*) newNode;
		newNode->prev = (LLNode*) cursor;
		newNode->next = (LLNode*) 0;
	}
}

template <> void LinkedList<Payload2>::savePayload(Payload2* mp) {
	//if the list is empty, then make payP be mp
	//else traverse the list,
	//make a new list element
	//put mp in that
	//attach the new list element to the existing list
	if(this->isEmpty())
	{
		head->payP = mp;
	}
	else
	{
		LLNode* cursor = head;
		while(cursor->next)
		{
			cursor=(LLNode*)cursor->next;
		}
		//now temp points to the last element

		//make a new element, attach mp to it, wire up the new element
		LLNode* newNode = new LLNode();
		newNode->payP = (Payload2*) mp;
		cursor->next = (LLNode*) newNode;
		newNode->prev = (LLNode*) cursor;
		newNode->next = (LLNode*) 0;
	}
}

template <class Payload> bool LinkedList<Payload>::isEmpty() {
	bool ans = false;
	if(head->payP == (Payload*)0)
	{
		ans = true;
	}
	return ans;
}

template <> Payload1* LinkedList<Payload1>::dequeueLIFO() {
	Payload1* payP = (Payload1*)0;
	if(this->isEmpty())
	{
		cout << "Trying to dequeue from empty." << endl;
	}
	else
	{
		LLNode* cursor = head;
		while(cursor->next)
		{
			cursor=(LLNode*)cursor->next;
		}
		//now cursor points to the last element


		payP = cursor->payP;
		cursor->payP = (Payload1*)0;
		cout << "Room being returned is " << payP->roomNumber << endl;
		//remove the last, now empty, element
		if(cursor->prev)
		{
			cursor=(LLNode*)cursor->prev;
			//free(cursor->next);
			cout << "end of queue is room " << cursor->payP->roomNumber << endl;
			cursor->next = (LLNode*)0;
		}
		else
		{
			cout << "Queue is now empty" << endl;
		}
		cout << "returning from dequeue" << endl;
	}

	return payP;
}


template <> Payload2* LinkedList<Payload2>::dequeueFIFO() {
	Payload2* payP = (Payload2*) 0;
	if (this->isEmpty()) {
		cout << "Trying to dequeue empty list" << endl;
	}
	payP = head->payP;
	if (head->next) {
		LLNode* temp = head;
		head = head->next;
		delete temp;
	}
	else {
		head->payP = (Payload2*) 0;
	}
	return payP;
}


template <> void LinkedList<Payload2>::printHistory() {
	cout << "Printing history" << endl;
	if(this->isEmpty())
	{
		cout << "Empty list" << endl;
	}
	else
	{
		//traverse the list, printing as we go
		float treasureSubtotal = 0.0;
		int room = -1;
		LLNode* temp = head;
		while(temp->next)
		{
			room = temp->payP->roomNumber;
			treasureSubtotal+= temp->payP->treasure;
			printf("The room was %d, and the treasure subtotal was %f.\n", room, treasureSubtotal);
			temp = temp->next;
		}
		room =temp->payP->roomNumber;
		treasureSubtotal+= temp->payP->treasure;
		printf("The room was %d, and the treasure subtotal was %f.\n", room, treasureSubtotal);
	}
}

template<> void LinkedList<Payload2>::writeHistory(char* filename) {
	ofstream outFile;
	outFile.open(filename);
	LLNode* cursor = head;
	float treasureTotal = 0;
	while (cursor->next) {
		treasureTotal += cursor->payP->treasure;
		outFile << cursor->payP->roomNumber << " " << treasureTotal << endl;
		cursor = cursor->next;
	}
	treasureTotal += cursor->payP->treasure;
	outFile << cursor->payP->roomNumber << " " << treasureTotal;
	outFile.close();
}

template<> void LinkedList<Payload1>::displayList() {
	LLNode* cursor = head;
	while (cursor->next) {
		cout << "Room Number: " << cursor->payP->roomNumber << endl;
		cout << "Treasure: " << cursor->payP->treasure << endl;
		cout << endl;
		cursor = cursor->next;
	}
	cout << "Room Number: " << cursor->payP->roomNumber << endl;
	cout << "Treasure: " << cursor->payP->treasure << endl;
	cout << endl;
}

template<> void LinkedList<Payload2>::displayList() {
	LLNode* cursor = head;
	while (cursor->next) {
		cout << "Room Number: " << cursor->payP->roomNumber<< endl;
		cout << "Treasure: " << cursor->payP->treasure << endl;
		cout << endl;
		cursor = cursor->next;
	}
	cout << "Room Number: " << cursor->payP->roomNumber << endl;
	cout << "Treasure: " << cursor->payP->treasure << endl;
	cout << endl;
}
