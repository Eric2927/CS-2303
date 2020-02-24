/*
 * Student.h
 *
 *  Created on: Feb 19, 2020
 *      Author: eric_li
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <string>

using namespace std;


template <class MyStruct> class Student {
public:
	Student(string, int);
	virtual ~Student();
	long ID;
	string name;
	long getID();
	string getName();
	int kys(MyStruct hi);
};

#endif /* STUDENT_H_ */
