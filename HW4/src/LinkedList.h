/*
 * LinkedList.h
 *
 *  Created on: Feb 23, 2020
 *      Author: eric_li
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Room.h"

struct SearchResults
{
	int roomNumber;
	float treasure;
};
typedef Room Payload;
typedef SearchResults Payload2;

template <class Payload>
class LinkedList {
private:
	struct LLNode
	{
		struct LLNode* next;
		struct LLNode* prev;
		Payload* payP;
	};
	LLNode* head;
public:
	LinkedList();
	virtual ~LinkedList();
	LLNode* removeFromList(Payload* pP);
	void savePayload(Payload* mp);
	bool isEmpty();
	Payload* dequeueLIFO();
	Payload* dequeueFIFO();
};

void printHistory(LinkedList<Payload2> searchHistory);

#endif /* LINKEDLIST_H_ */
