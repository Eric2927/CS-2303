/*
 * Production.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Production.h"
#include "LinkedList.h"
#include <stdbool.h>
#include <iostream>

using namespace std;

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[]) {
	bool answer = false;

	if(argc <=1) //no interesting information
	{
		cout << "Didn't find any arguments." << endl;
		answer = false;
	}
	else if (argc == 2) {
		cout << "Please provide a room limit and a treasure limit." << endl;
	}
	else if (argc == 3) {
		cout << "Please provide a treasure limit." << endl;
	}
	else //there is interesting information
	{
		cout << "Found " << argc-1 << " interesting arguments." << endl;
		char filename[FILENAMELENGTHALLOWANCE];
		char* eptr=(char*) malloc(sizeof(char*));
		long aL=-1L;
		int maxRooms;
		float maxTreasure;
		double maxTreas;
		bool proceedWithSearch = true;
		for(int i = 1; i<argc; i++) //don't want to read argv[0]
		{//argv[i] is a string
			//in this program our arguments are NR, NC, gens, filename, print and pause
			//because pause is optional, argc could be 6 or 7
			//because print is optional (if print is not present, neither is pause) argc could be 5
			switch(i)
			{
			case 1:
				//this is filename
				cout << "The length of the filename is " << strlen(argv[i]) << endl;
				cout << "The proposed filename is " << argv[i] << endl;
				if(strlen(argv[i])>=FILENAMELENGTHALLOWANCE)
				{
					cout << "Filename is too long." << endl;
					answer = false;
				}
				else
				{
					strcpy(filename, argv[i]);
					cout << "Filename was " << filename << endl;
				}
				break;
			case 2:
				//this is maximum number of rooms

				aL= strtol(argv[i], &eptr, 10);
				maxRooms = (int) aL;
				if (maxRooms <= 0) {
					proceedWithSearch = false;
					answer = false;
				}
				cout << "Number of rooms is " << maxRooms << endl;
				break;
			case 3:
				//this is maximum amount of treasure

				maxTreas = atof(argv[i]);
				if (maxTreas <= 0) {
					proceedWithSearch = false;
					answer = false;
				}
				cout << "Amount of treasure is " << maxTreas << endl;
				maxTreasure = (float) maxTreas;
				break;

			default:
				cout << "Unexpected argument count." << endl;
				proceedWithSearch = false;
				answer = false;
				break;
			}//end of switch
		}//end of for loop on argument count

		// If arguments are all reasonable
		if (proceedWithSearch) {
			cout << "after reading arguments" << endl;
			//we'll want to read the file
			int nrooms = -1;


			AdjMat* adjMP = new AdjMat(); // TODO CHECK THIS


			//cannot, do not know nrooms init(adjMP);
			//puts("Back from init Adj Mat"); fflush(stdout);
			Room** theRoomPs = new Room*[10];//addresses for 10 rooms

			cout << "Before read file" << endl;
			answer = readFile(filename, &nrooms, adjMP, theRoomPs); //read the file
			cout << "Back from read file" << endl;

			//we'll want to conduct the search
			//for the search we'll need an empty search history
			LinkedList<SearchResults>* historyP = new LinkedList<SearchResults>();
			//we'll need the Queue, into which we put rooms, and remove rooms
			LinkedList<Room>* searchQ = new LinkedList<Room>();
			cout << "starting search" << endl;
			//we'll start searching with room 0
			bool done = false;
			int searchedRooms = 0;
			float foundTreasure = 0.0;
			Room* roomBeingSearchedP = theRoomPs[0];
			//we set its searched field to true, and take its treasure
			roomBeingSearchedP->searched = true;
			//we record it in the history
			SearchResults* srP = new SearchResults();
			srP->roomNumber= 0;
			srP->treasure = roomBeingSearchedP->treasure;
			if((srP->treasure <= maxTreas) && (maxRooms>0))
			{
				//here we are enqueueing room 0
				cout << "Enqueuing room 0" << endl;
				//TODO: what else goes here?
				// I am going to include the following line because the print statement above suggests this, but
				// this code makes the program search the first room twice if none of the limits (room/treasure limit)
				// are reached at the end of the search process.
				searchQ->savePayload(roomBeingSearchedP);
				historyP->savePayload(srP);
				foundTreasure += roomBeingSearchedP->treasure;
				searchedRooms ++;
			}

			while(!done)
			{   //here we want to find all of the rooms adjacent to the roomBeingSearched,
				//so we look in the adj matrix
				for(int col = 0; (col<nrooms)&&!done; col++)
				{
					//we check whether this room is neighboring
					printf("checking rooms %d and %d.\n", roomBeingSearchedP->roomNumber, col); fflush(stdout);
					if(adjMP->getEdge(roomBeingSearchedP->roomNumber, col) == 1)
					{
						cout << "found an edge" << endl;
						//if so, we check whether room has been searched
						if(!(theRoomPs[col]->searched))
						{//if it hasn't been searched
							printf("Room %d hasn't already been searched.\n", col);
							//we set it to searched
							theRoomPs[col]->searched=true;
							if(searchedRooms < maxRooms && foundTreasure + theRoomPs[col]->treasure < maxTreasure)
								//we check whether we can take the treasure vs. limit
								//we check whether we've hit the room limit
							{//we enqueue it for search
								foundTreasure += theRoomPs[col]->treasure;
								searchedRooms ++;
								printf("found treasure updated to %f.\n", foundTreasure);
								printf("enqueuing room %d.\n", col); fflush(stdout);
								printf("Before enqueuing, queue empty reports %d\n", searchQ->isEmpty());
								searchQ->savePayload(theRoomPs[col]);
								srP = new SearchResults();
								srP->roomNumber=theRoomPs[col]->roomNumber;
								srP->treasure = theRoomPs[col]->treasure;
								historyP->savePayload(srP);
								printf("After enqueuing, queue empty reports %d\n", searchQ->isEmpty());
								//searchQ->displayList();
								//historyP->displayList();
							}//check about search limits
						}//room can still be searched
					}//room is a neighbor

					if(foundTreasure >= maxTreasure)
					{
						done = true;
						cout << "Done by treasure" << endl;
					}
					if (searchedRooms>=maxRooms)
					{
						done = true;
						cout << "Done by rooms" << endl;
					}
				}//scan for all possible rooms to search from this room
				//time to get the next room
				if(searchQ->isEmpty())
				{
					done=true;
					cout << "Done by queue empty" << endl;
				}
				if(!done)
				{
					cout << "Invoking dequeue" << endl;
					roomBeingSearchedP = searchQ->dequeueLIFO();
				}
			}//while search is not done
			//search is now done, time to print the history
			historyP->printHistory();
			char* outputFilename = "outputFile.txt";
			historyP->writeHistory(outputFilename);
		}
		else {
			cout << "Search was not conducted" << endl;
		}


	}//end of else we have good arguments

	return answer;
}

bool Production::readFile(char* filename, int* nrooms, AdjMat* adjMP, Room** theRoomPs) {
	bool ok = false;
	//the file tells how many rooms there are
	FILE* fp = fopen(filename, "r"); //read the file

	if (fp == NULL)
	{
		puts("Error! opening file");

	}
	else
	{
		fscanf(fp,"%d", nrooms);
		cout << "Before initializing Adj mat" << endl;
		adjMP->init(*nrooms);
		int temp = -1;
		for(int roomr = 1; roomr<*nrooms; roomr++)
		{
			printf("on row %d\n", roomr);fflush(stdout);
			for(int roomc = 0; roomc<roomr; roomc++)
			{
				fscanf(fp,"%d", &temp);
				printf("in column %d, read %d\n", roomc, temp);fflush(stdout);
				//now set the value in the adjacency matrix
				if(temp==1)
				{
					adjMP->setEdge(roomr, roomc);
				}
			}
		}

		float tempTreas = 2.9;
		for(int roomr = 0; roomr<*nrooms; roomr++)
		{
			fscanf(fp,"%f", &tempTreas);
			//make a room and set its treasure
			Room** aRoomP = theRoomPs;
			aRoomP = aRoomP+roomr;
			*aRoomP = new Room();
			//now set the treasures
			(*aRoomP)->treasure = tempTreas;
			(*aRoomP)->roomNumber = roomr;
			printf("The treasure in room %d is %f\n", roomr, (*aRoomP)->treasure);
		}
		ok = true;
	}
	fclose(fp);

	return ok;
}
