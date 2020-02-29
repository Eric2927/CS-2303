/*
 * AdjMat.h
 *
 *  Created on: Feb 26, 2020
 *      Author: eric_li
 */

#ifndef ADJMAT_H_
#define ADJMAT_H_

class AdjMat {
private:
	int n;
	int* edgesP;
public:
	AdjMat();
	virtual ~AdjMat();
	void setEdge(int row, int col);
	int getEdge(int row, int col);
	void init(int dimension);
	void display();
};

#endif /* ADJMAT_H_ */
