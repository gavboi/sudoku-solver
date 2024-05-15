#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>

// size must be square number
#define SIZE 4
// 1 to space squares in print, 0 to pack
#define SPACED 1
#define VERBOSE 1

int d();
int section_check(int* arr);
int is_section_complete(int* arr);
int is_puzzle_complete(int* cells);
int* get_row(int* cells, int index);
int* get_column(int* cells, int index);
int* get_box(int* cells, int index);
int print_section(int* cells);
int print_puzzle(int* cells);

int main() {
	printf("=== SUDOKU SOLVER ===\n");
	// setup variables and functions
	double square_test = sqrt(SIZE);
	if (square_test != (int)square_test) {
		printf("ERROR: SIZE = %d is not a square number!\n", SIZE);
		return 1;
	}
	// values stored 1d, left to right then top to bottom
	int *cells = (int *)malloc(SIZE * SIZE * sizeof(int));
	int *section = (int *)malloc(SIZE * sizeof(int));
	char input;
	int index;
	
	// get input
	printf("Enter sudoku puzzle line by line (%d lines)\n", SIZE);
	printf("and use 0 for unknown cells:\n\n");
	printf("%.*s\n", SIZE, "vvvvvvvvvvvvvvvvvvvvvvvvvvvv");
	for (int row_num = 0; row_num < SIZE; row_num++) {
		index = 0;
		while ((input = getchar()) && index < SIZE) {
			if (input != '\n' && input != ' ') {
				*(cells + (index++) + row_num*SIZE) = input - '0';
			}
		}
	}
	
	// confirm input
	printf("\nPuzzle received:\n\n");
	print_puzzle(cells);
	printf("\n");
	
	// solve
	is_puzzle_complete(cells);
	// TODO
	
	// free
	printf("\n....................\n");
	printf("Freeing memory\n");
	free(cells);
	free(section);
	
	printf("Done\n\n");
	return 0;
}

int d() {
	printf(".");
}

int section_check(int* arr) {
	/* Returns an int where the nth byte is 1 if n is present in `arr`.
	 * `arr` must be length `SIZE`. Returns -1 if n occurs more than
	 * once. */
	int total = 0;
	int current;
	for (int i = 0; i < SIZE; i++) {
		if (*(arr + i) > 0) {
			current = 1 << (*(arr + i) - 1);
			if ((total & current) != 0) {
				if (VERBOSE) {
					printf("2 instances of %d!\n", *(arr + i));
				}
				return -1;
			}
			total |= current;
		}
	}
	return total;
}	

int is_section_complete(int* arr) {
	/* Checks if a section `arr` of length `SIZE` contains all elements
	 * from 1 to `SIZE`. Returns 1 if yes, 0 if no. */
	int check = section_check(arr);
	if (check == pow(2, SIZE) - 1) {
		return 1;
	}
	print_section(arr);
	return 0;
}

int is_puzzle_complete(int* cells) {
	/* Checks if all rows, columns and boxes are complete sections.
	 * Returns 1 if yes, 0 if no. */
	int *section = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		section = get_row(cells, i);
		if (is_section_complete(section) == 0) {
			if (VERBOSE) {
				printf("Row index %d incomplete\n", i);
			}
			free(section);
			return 0;
		}
		section = get_column(cells, i);
		if (is_section_complete(section) == 0) {
			if (VERBOSE) {
				printf("Column index %d incomplete\n", i);
			}
			free(section);
			return 0;
		}
		section = get_box(cells, i);
		if (is_section_complete(section) == 0) {
			if (VERBOSE) {
				printf("Box index %d incomplete\n", i);
			}
			free(section);
			return 0;
		}
	}
	free(section);
	printf("Complete!\n");
	return 1;
}

int* get_row(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in row
	 * `index`. */
	int *row = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(row + i) = *(cells + i + index*SIZE);
	}
	return row;
}

int* get_column(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in column
	 * `index`. */
	int *col = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(col + i) = *(cells + index + i*SIZE);
	}
	return col;
}

int* get_box(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in box
	 * `index`. */
	int *box = (int *)malloc(SIZE * sizeof(int));
	int root = (int)sqrt(SIZE);
	int row = index / root;
	int offset = index % root;
	int base_offset = SIZE*root*row + root*offset;
	for (int i = 0; i < SIZE; i++) {
		*(box + i) = *(cells + base_offset + i + (SIZE-root)*(int)(i/root));
	}
	return box;
}

int print_section(int* arr) {
	/* Prints contents of `arr` in a row, with spacing if required.
	 * `arr` must be length `SIZE`. */
	int root = (int)sqrt(SIZE);
	for (int i = 0; i < SIZE; i++) {
		if (SPACED && i != 0 && i % root == 0) {
			printf(" | ");
		}
		printf("%d", *(arr + i));
	}
	printf("\n");
	return 0;
}

int print_puzzle(int* cells) {
	/* Prints contents of `cells` as a full puzzle with spacing if
	 * required. */
	int root = (int)sqrt(SIZE);
	for (int y = 0; y < SIZE; y++) {
		if (SPACED && y != 0 && y % root == 0) {
			printf("%.*s\n", SIZE + 3*(root-1), "-------------------------");
		}
		print_section(cells + y*SIZE);
	}
	return 0;
}

// THURSDAY -> store what can be put in
// FRIDAY -> generate puzzles