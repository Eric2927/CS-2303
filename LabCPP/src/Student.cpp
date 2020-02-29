/*
 * Student.cpp
 *
 *  Created on: Feb 19, 2020
 *      Author: eric_li
 */

#include "Student.h"

Student::Student() {
}

Student::~Student() {
}


char* Student::getName() {
	return name;
}

void Student::setName(char* aName) {
	name = aName;
}
