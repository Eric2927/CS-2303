/*
 * Student.cpp
 *
 *  Created on: Feb 19, 2020
 *      Author: eric_li
 */

#include "Student.h"

Student::Student(string name, int ID) {
	this->name = name;
	this->ID = ID;
}

Student::~Student() {
}

long Student::getID() {
	return ID;
}

string Student::getName() {
	return name;
}
