/*
 * Student.cpp
 *
 *  Created on: Feb 19, 2020
 *      Author: eric_li
 */

#include "Student.h"

template <class MyStruct> Student<MyStruct>::Student(string name, int ID) {
	this->name = name;
	this->ID = ID;
}

template <class MyStruct> Student<MyStruct>::~Student() {
}

template <class MyStruct> long Student<MyStruct>::getID() {
	return ID;
}

template <class MyStruct> string Student<MyStruct>::getName() {
	return name;
}
