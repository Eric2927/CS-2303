//============================================================================
// Name        : LabCPP.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "Student.h"

int main() {
	cout << "Hello World" << endl;

	Student<int>* aStudent = new Student<int>("Eric", 831881924);
	cout << "Name: " << aStudent->getName() << endl;
	cout << "ID: " << aStudent->getID() << endl;
	return 0;
}
