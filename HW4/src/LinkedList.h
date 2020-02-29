/*
 * LinkedList.h
 *
 *  Created on: Feb 23, 2020
 *      Author: eric_li
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Room.h"
#include <fstream>

struct SearchResults
{
	int roomNumber;
	float treasure;
};
typedef Room Payload1;
typedef SearchResults Payload2;

template <class Payload>
class LinkedList {
private:
	struct LLNode
	{
		LLNode() {
			next = (LLNode*) 0;
			prev = (LLNode*) 0;
			payP = (Payload*) 0;
		}
		struct LLNode* next;
		struct LLNode* prev;
		Payload* payP;
	};
	LLNode* head;
public:
	LinkedList();
	virtual ~LinkedList();
	void removeFromList(Payload* pP);
	void savePayload(Payload* mp);
	bool isEmpty();
	Payload* dequeueLIFO();
	Payload* dequeueFIFO();
	void printHistory();
	void writeHistory(char* filename);
	void displayList();
};

#endif /* LINKEDLIST_H_ */
