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
#include "WpiStudent.h"

int main() {
	cout << "Hello World" << endl;
	Wpi_Student* aStudent = new Wpi_Student();
	char* myName = "Eric";
	int myID = 12345;
	aStudent->setName(myName);
	aStudent->setID(myID);
	cout << "My Name: " << aStudent->getName() << endl;
	cout << "My ID: " << aStudent->getID() << endl;
}
