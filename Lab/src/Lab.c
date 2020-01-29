/*
 ============================================================================
 Name        : Lab.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int width = 2;
	int height = 3;
	int myArray[height][width];
	for (int i = 0; i < height; i ++) {
		for (int j = 0; j < width; j ++) {
			myArray[i][j] = 1;
		}
	}
	for (int i = 0; i < height; i ++) {
		for (int j = 0; j < width; j ++) {
			printf("%d ", myArray[i][j]);
		}
		puts("");
	}
	return EXIT_SUCCESS;
}
