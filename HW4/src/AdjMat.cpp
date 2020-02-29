/*
 * AdjMat.cpp
 *
 *  Created on: Feb 26, 2020
 *      Author: eric_li
 */

#include "AdjMat.h"
#include <iostream>

using namespace std;

AdjMat::AdjMat() {
	n = 0;
	edgesP = new int[0];
}

AdjMat::~AdjMat() {
}

void AdjMat::init(int dimension) {
	n = dimension;
	edgesP = new int[n*n];
	for(int row = 0; row< dimension; row++)
	{
		for(int col = 0; col< dimension; col++)
		{
			edgesP[(row*n) + col] = 0;
		}
	}
}

void AdjMat::setEdge(int row, int col) {
	edgesP[(n*row) + col] = 1;
	edgesP[(n*col) + row] = 1;
}

int AdjMat::getEdge(int row, int col) {
	return edgesP[(n*row) + col];
}

void AdjMat::display() {
	cout << "Displaying..." << endl;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			cout << edgesP[n*i + j] << " ";
		}
		cout << endl;
	}
}
