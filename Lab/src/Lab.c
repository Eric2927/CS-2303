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

int main(int argc, char* argv[]) {
	/* Lab 2
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
	*/

	/* Lab 3
	printf("Number of arguments: %d\n"
			"The arguments are:\n\n", argc - 1);

	for (int i = 1; i < argc; i ++) {
		printf("%s\n\n", argv[i]);
	}
	*/

	/* Lab 4
	char* strings[] = {"Hi", "two", "nice"};
	FILE* myFile = fopen("strings.txt", "w");
	fputs(strings[1], myFile);
	*/


	return EXIT_SUCCESS;
}
