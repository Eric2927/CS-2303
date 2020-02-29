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


class Student {
private:
	char* name;
public:
	Student();
	virtual ~Student();
	char* getName();
	void setName(char* aName);
};

#endif /* STUDENT_H_ */
