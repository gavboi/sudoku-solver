#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <math.h>
#include "helpers.h"
#include "params.h"


int mark_cells_blocked_by_value(int* cells, int* blocked_numbers, int index);
int section_check(int* arr);
int is_section_complete(int* arr);
int is_puzzle_complete(int* cells);
int print_section(int* cells);
int print_puzzle(int* cells);

int main(int argc, char **argv) {
	// setup variables and functions
	char input;
	int index;
	int value;
	double d_value;
	int complete;
	int changed;
	int latest;
	// parsing options
	int opt;
	while ((opt = getopt(argc, argv, "ghs:v")) != -1) {
		switch (opt) {
			case 's':
				value = atoi(optarg);
				if (setSize(value) != 0) {
					printf("Invalid size! (size = %d)\n", value);
					return 1;
				}
				break;
			case 'g':
				setSpaced(1);
				break;
			case 'v':
				setVerbose(1);
				break;
			case 'h':
			case '?':
			default:
				printf("Usage: %s [-s grid-size] [-g] [-v]\n", argv[0]);
				printf("   s: set puzzle width/height\n");
				printf("   g: format puzzle prints in grid\n");
				printf("   v: enable debug prints\n");
				return 1;
		}
	}
	// values stored 1d, left to right then top to bottom
	int *cells = (int *)malloc(getSize() * getSize() * sizeof(int));
	int *blocked_numbers = (int *)malloc(getSize() * getSize() * sizeof(int));
	int *section;
	
	// get input
	printf("=== SUDOKU SOLVER ===\n");
	printf("Enter sudoku puzzle line by line (%d lines)\n", getSize());
	printf("and use 0 for unknown cells:\n\n");
	printf("%.*s\n", getSize(), "vvvvvvvvvvvvvvvvvvvvvvvvvvvv");
	for (int row_num = 0; row_num < getSize(); row_num++) {
		index = 0;
		while ((input = getchar()) && index < getSize()) {
			if (input != '\n' && input != ' ') {
				*(cells + (index++) + row_num*getSize()) = input - '0';
			}
		}
	}
	
	// confirm input
	if (getVerbose()) {
		printf("\nPuzzle received:\n\n");
		print_puzzle(cells);
	}
	printf("\n");
	
	// solve
	printf("Working...\n");
	// initial fill all possible
	for (int i = 0; i < getSize()*getSize(); i++) {
		*(blocked_numbers + i) = 0;
	}
	// update to current values
	for (int i = 0; i < getSize()*getSize(); i++) {
		if (*(cells + i) != 0) {
			mark_cells_blocked_by_value(cells, blocked_numbers, i);
		} else {
			if (getVerbose()) {
				printf("cell %d is empty\n", i);
			}
		}
	}
	/* actual solve: go through puzzle until empty cell is found, then
	 * see if there is only one option, fill it if yes. If not, check
	 * cell's sections to see if it contains the only spot for a given
	 * value, fill it if yes. If whole puzzle is searched with no
	 * changes, choose one possible value. */
	while ((complete = is_puzzle_complete(cells)) == 0) {
		changed = 0;
		// value is only option for cell
		for (int i = 0; i < getSize()*getSize(); i++) {
			value = *(cells + i);
			if (value == 0) {
				latest = i;
				d_value = bit_flip(*(blocked_numbers + i));
				d_value = log(d_value) / log(2);
				if (d_value == (value = (int)d_value)) {
					value += 1;
					changed = 1;
					*(cells + i) = value;
					mark_cells_blocked_by_value(cells, blocked_numbers, i);
					if (getVerbose()) {
						printf("Setting cell %d = %d (only option)\n", i, value);
					}
					continue;
				}
			}
		}
		// only cell in section for value
		for (int s = 0; s < getSize(); s++) {
			section = cells_in_row(s);
			for (int v = 0; v < getSize(); v++) {
				index = -1;
				for (int i = 0; i < getSize(); i++) {
					value = *(blocked_numbers + *(section + i));
					if (((value >> v) & 1) == 0) {
						if (index == -1) {
							index = i;
						} else {
							index = -2; 
							break;
						}
					} 
				}
				if (index >= 0) {
					value = v + 1;
					changed = 1;
					index = *(section + index);
					*(cells + index) = value;
					mark_cells_blocked_by_value(cells, blocked_numbers, index);
					if (getVerbose()) {
						printf("Setting cell %d = %d (section option)\n", index, value);
					}
					break;
				}
			}
			free(section);
			section = cells_in_column(s);
			for (int v = 0; v < getSize(); v++) {
				index = -1;
				for (int i = 0; i < getSize(); i++) {
					value = *(blocked_numbers + *(section + i));
					if (((value >> v) & 1) == 0) {
						if (index == -1) {
							index = i;
						} else {
							index = -2; 
							break;
						}
					} 
				}
				if (index >= 0) {
					value = v + 1;
					changed = 1;
					index = *(section + index);
					*(cells + index) = value;
					mark_cells_blocked_by_value(cells, blocked_numbers, index);
					if (getVerbose()) {
						printf("Setting cell %d = %d (section option)\n", index, value);
					}
					break;
				}
			}
			free(section);
			section = cells_in_box(s);
			for (int v = 0; v < getSize(); v++) {
				index = -1;
				for (int i = 0; i < getSize(); i++) { 
					value = *(blocked_numbers + *(section + i));
					if (((value >> v) & 1) == 0) {
						if (index == -1) {
							index = i;
						} else {
							index = -2; 
							break;
						}
					} 
				}
				if (index >= 0) {
					value = v + 1;
					changed = 1;
					index = *(section + index);
					*(cells + index) = value;
					mark_cells_blocked_by_value(cells, blocked_numbers, index);
					if (getVerbose()) {
						printf("Setting cell %d = %d (section option)\n", index, value);
					}
					break;
				}
			}
			free(section);
		}
		if (changed) {continue;}
		// choose one; take farthest 0 cell into puzzle and smallest number
		value = *(blocked_numbers + latest);
		for (int v = 0; v < getSize(); v++) {
			if (((value >> v) & 1) == 0) {
				value = v + 1;
				changed = 1;
				break;
			}
		}
		if (!changed) {
			printf("Puzzle entered state with unfillable cells!\n\n");
			print_puzzle(cells);
			printf("\n");
			return 1;
		}
		*(cells + latest) = value;
		mark_cells_blocked_by_value(cells, blocked_numbers, latest);
		if (getVerbose()) {
			printf("Setting cell %d = %d (random)\n", latest, value);
		}
	}
	
	if (complete == -1) {
		printf("ERROR: Puzzle entered invalid state!\n");
	}	
	printf("\n");
	print_puzzle(cells);
	
	// free
	if (getVerbose()) {
		printf("\nFreeing memory\n");
	}
	free(cells);
	free(blocked_numbers);
	
	printf("\nDone\n\n");
	return 0;
}

int mark_cells_blocked_by_value(int* cells, int* blocked_numbers, int index) {
	/* Updates `blocked_numbers` to reflect the value placed at `index`
	 * in `cells`. Will update row, column, and box. */
	*(blocked_numbers + index) = pow(2, getSize()) - 1;
	int value = bit_shift(*(cells + index));
	int *arr;
	arr = (int *)cells_in_row(cell_to_row(index));
	for (int i = 0; i < getSize(); i++) {
		*(blocked_numbers + *(arr + i)) |= value;
	}
	free(arr);
	arr = (int *)cells_in_column(cell_to_column(index));
	for (int i = 0; i < getSize(); i++) {
		*(blocked_numbers + *(arr + i)) |= value;
	}
	free(arr);
	arr = (int *)cells_in_box(cell_to_box(index));
	for (int i = 0; i < getSize(); i++) {
		*(blocked_numbers + *(arr + i)) |= value;
	}
	free(arr);
	return 0;
}

int section_check(int* arr) {
	/* Returns an int where the nth byte is 1 if n is present in `arr`.
	 * `arr` must be length `size`. Returns -1 if n occurs more than
	 * once. */
	int total = 0;
	int current;
	for (int i = 0; i < getSize(); i++) {
		if (*(arr + i) > 0) {
			current = 1 << (*(arr + i) - 1);
			if ((total & current) != 0) {
				if (getVerbose()) {
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
	/* Checks if a section `arr` of length `size` contains all elements
	 * from 1 to `size`. Returns 1 if yes, 0 if no, -1 if already
	 * invalid. */
	int check = section_check(arr);
	if (check == pow(2, getSize()) - 1) {return 1;}
	if (check == -1) {return -1;}
	return 0;
}

int is_puzzle_complete(int* cells) {
	/* Checks if all rows, columns and boxes are complete sections.
	 * Returns 1 if yes, 0 if no, -1 if invalid. */
	int *section;
	int section_complete;
	for (int i = 0; i < getSize(); i++) {
		section = get_row_values(cells, i);
		section_complete = is_section_complete(section);
		free(section);
		if (section_complete == -1) {return -1;}
		if (section_complete == 0) {
			if (getVerbose()) {
				printf("Row index %d incomplete\n", i);
			}
			return 0;
		}
		section = get_column_values(cells, i);
		section_complete = is_section_complete(section);
		free(section);
		if (section_complete == -1) {return -1;}
		if (section_complete == 0) {
			if (getVerbose()) {
				printf("Column index %d incomplete\n", i);
			}
			return 0;
		}
		section = get_box_values(cells, i);
		section_complete = is_section_complete(section);
		free(section);
		if (section_complete == -1) {return -1;}
		if (section_complete == 0) {
			if (getVerbose()) {
				printf("Box index %d incomplete\n", i);
			}
			return 0;
		}
	}
	printf("Complete!\n");
	return 1;
}

int print_section(int* arr) {
	/* Prints contents of `arr` in a row, with spacing if required.
	 * `arr` must be length `size`. */
	int root = (int)sqrt(getSize());
	for (int i = 0; i < getSize(); i++) {
		if (getSpaced() && i != 0 && i % root == 0) {
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
	int root = (int)sqrt(getSize());
	for (int y = 0; y < getSize(); y++) {
		if (getSpaced() && y != 0 && y % root == 0) {
			printf("%.*s\n", getSize() + 3*(root-1), "-------------------------");
		}
		print_section(cells + y*getSize());
	}
	return 0;
}
