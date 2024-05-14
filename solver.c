#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define SIZE 3

int d();
int is_complete(int* cells);
int* get_row(int* cells, int index);
int* get_column(int* cells, int index);
int* get_box(int* cells, int index);
int print_puzzle(int* cells);

int main() {
	printf("=== SUDOKU SOLVER ===\n");
	// setup variables and functions
	// values stored 1d, left to right then top to bottom
	int *cells = (int *)malloc(SIZE * SIZE * sizeof(int));
	char input;
	int index;
	
	// get input
	printf("Enter sudoku puzzle line by line (%d lines)\n", SIZE);
	printf("and use 0 for unknown cells:\n\n");
	for (int row_num = 0; row_num < SIZE; row_num++) {
		index = 0;
		while ((input = getchar()) && index < SIZE) {
			if (input != '\n' && input != ' ') {
				*(cells + (index++) + row_num*SIZE) = input - '0';
			}
		}
	}
	
	// confirm input
	printf("\nPuzzle received:\n");
	print_puzzle(cells);
	
	// solve
	// TODO
	
	// free
	printf("Freeing memory...");
	free(cells);
	return 0;
}

int d() {
	printf(".");
}

int is_complete(int* cells) {
	// TODO: bitwise 511 from array
	return 0;
}

int* get_row(int* cells, int index) {
	int *row = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(row + i) = *(cells + i + index*SIZE);
	}
	return row;
}

int* get_column(int* cells, int index) {
	int *col = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(col + i) = *(cells + index + i*SIZE);
	}
	return col;
}

int* get_box(int* cells, int index) {
	//TODO
}

int print_puzzle(int* cells) {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			printf("%d", *(cells + x + y*SIZE));
		}
		printf("\n");
	}
	return 0;
}

// TODO
// - solving algorithms