/*
 * WpiStudent.h
 *
 *  Created on: Feb 26, 2020
 *      Author: eric_li
 */

#ifndef WPISTUDENT_H_
#define WPISTUDENT_H_

#include "Student.h"

class Wpi_Student : public Student {
private:
	int id;
public:
	Wpi_Student();
	virtual ~Wpi_Student();
	int getID();
	void setID(int id);
};

#endif /* WPISTUDENT_H_ */
