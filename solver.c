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
int bit_shift(int val);
int find_cell(int x, int y);
int cell_to_row(int cell);
int* cells_in_row(int row);
int* get_row_values(int* cells, int index);
int cell_to_column(int cell);
int* cells_in_column(int col);
int* get_column_values(int* cells, int index);
int cell_to_box(int cell);
int* cells_in_box(int box);
int* get_box_values(int* cells, int index);
int mark_cells_blocked_by_value(int* blocked_numbers, int* cells, int value);
int section_check(int* arr);
int is_section_complete(int* arr);
int is_puzzle_complete(int* cells);
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
	int *blocked_numbers = (int *)malloc(SIZE * SIZE * sizeof(int));
	int *section = (int *)malloc(SIZE * sizeof(int));
	char input;
	int index;
	int value;
	
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
	// initial fill all possible
	for (int i = 0; i < SIZE*SIZE; i++) {
		*(blocked_numbers + i) = 0;
	}
	// update to current values
	for (int i = 0; i < SIZE*SIZE; i++) {
		if (*(cells + i) != 0) {
			value = bit_shift(*(cells + i));
			section = (int *)cells_in_row(cell_to_row(i));
			mark_cells_blocked_by_value(blocked_numbers, section, value);
			section = (int *)cells_in_column(cell_to_column(i));
			mark_cells_blocked_by_value(blocked_numbers, section, value);
			section = (int *)cells_in_box(cell_to_box(i));
			mark_cells_blocked_by_value(blocked_numbers, section, value);
		} else {
			printf("cell %d is empty\n", i);
		}
		print_puzzle(blocked_numbers);
		printf("======\n\n");
	}
	is_puzzle_complete(cells);
	// TODO
	
	// free
	printf("\n....................\n");
	printf("Freeing memory\n");
	free(cells);
	free(blocked_numbers);
	free(section);
	
	printf("Done\n\n");
	return 0;
}

int d() {
	printf(".");
}

int bit_shift(int val) {
	/* Returns an int with 1 in the `val`'th bit. */
	int result = 1 << (val - 1);
	return result;
}

int find_cell(int x, int y) {
	int cell = x + y*SIZE;
	return cell;
}

int cell_to_row(int cell) {
	/* Returns the row number containing the given cell. */
	int row = cell / SIZE;
	return row;
}

int* cells_in_row(int row) {
	/* Returns list of cell indexes in the given row. */
	int *arr = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(arr + i) = i + row*SIZE;
	}
	return arr;
}

int* get_row_values(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in row
	 * `index`. */
	int *row = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(row + i) = *(cells + i + index*SIZE);
	}
	return row;
}

int cell_to_column(int cell) {
	/* Returns the column number containing the given cell. */
	int col = cell % SIZE;
	return col;
}

int* cells_in_column(int col) {
	/* Returns list of cell indexes in the given column. */
	int *arr = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(arr + i) = col + i*SIZE;
	}
	return arr;
}

int* get_column_values(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in column
	 * `index`. */
	int *col = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++) {
		*(col + i) = *(cells + index + i*SIZE);
	}
	return col;
}

int cell_to_box(int cell) {
	/* Returns the box number containing the given cell. */
	int rt = (int)sqrt(SIZE);
	int box = rt*(int)(cell_to_row(cell)/rt) + cell_to_column(cell)/rt;
	return box;
}

int* cells_in_box(int box) {
	/* Returns list of cell indexes in the given box. */
	int *arr = (int *)malloc(SIZE * sizeof(int));
	int root = (int)sqrt(SIZE);
	int row = box / root;
	int offset = box % root;
	int base_offset = SIZE*root*row + root*offset;
	for (int i = 0; i < SIZE; i++) {
		*(arr + i) = base_offset + i + (SIZE-root)*(int)(i/root);
	}
	return arr;
}

int* get_box_values(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in box
	 * `index`. */
	int *box = cells_in_box(index);
	for (int i = 0; i < SIZE; i++) {
		*(box + i) = *(cells + *(box + i));
	}
	return box;
}

int mark_cells_blocked_by_value(int* blocked_numbers, int* cells, int value) {
	for (int i = 0; i < SIZE; i++) {
		int current = *(blocked_numbers + *(cells + i));
		printf(",,,,,,,,,,,,,,,(%d) %d | %d = %d\n", *(cells + i), current, value, current|value);
		*(blocked_numbers + *(cells + i)) |= value;
	}
	return 0;
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
	 * from 1 to `SIZE`. Returns 1 if yes, 0 if no, -1 if already
	 * invalid. */
	int check = section_check(arr);
	if (check == pow(2, SIZE) - 1) {return 1;}
	if (check == -1) {return -1;}
	print_section(arr);
	return 0;
}

int is_puzzle_complete(int* cells) {
	/* Checks if all rows, columns and boxes are complete sections.
	 * Returns 1 if yes, 0 if no, -1 if invalid. */
	int *section = (int *)malloc(SIZE * sizeof(int));
	int section_complete;
	for (int i = 0; i < SIZE; i++) {
		section = get_row_values(cells, i);
		section_complete = is_section_complete(section);
		if (section_complete == -1) {return -1;}
		if (section_complete == 0) {
			if (VERBOSE) {
				printf("Row index %d incomplete\n", i);
			}
			free(section);
			return 0;
		}
		section = get_column_values(cells, i);
		section_complete = is_section_complete(section);
		if (section_complete == -1) {return -1;}
		if (section_complete == 0) {
			if (VERBOSE) {
				printf("Column index %d incomplete\n", i);
			}
			free(section);
			return 0;
		}
		section = get_box_values(cells, i);
		section_complete = is_section_complete(section);
		if (section_complete == -1) {return -1;}
		if (section_complete == 0) {
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