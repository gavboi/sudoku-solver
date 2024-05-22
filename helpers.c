#include <stdlib.h>
#include <math.h>
#include "helpers.h"
#include "params.h"

int bit_shift(int val) {
	/* Returns an int with 1 in the `val`'th bit. */
	int result = 1 << (val - 1);
	return result;
}

int bit_flip(int val) {
	/* Returns the number with bits relevant to `size` flipped. */
	int result = val ^ (int)(pow(2, getSize()) - 1);
	return result;
}

int find_cell(int x, int y) {
	/* Finds list index of cell coordinates `x`,`y`. */
	int cell = x + y*getSize();
	return cell;
}

int cell_to_row(int cell) {
	/* Returns the row number containing the given cell. */
	int row = cell / getSize();
	return row;
}

int* cells_in_row(int row) {
	/* Returns list of cell indexes in the given row. */
	int *arr = (int *)malloc(getSize() * sizeof(int));
	for (int i = 0; i < getSize(); i++) {
		*(arr + i) = i + row*getSize();
	}
	return arr;
}

int* get_row_values(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in row
	 * `index`. */
	int *row = (int *)malloc(getSize() * sizeof(int));
	for (int i = 0; i < getSize(); i++) {
		*(row + i) = *(cells + i + index*getSize());
	}
	return row;
}

int cell_to_column(int cell) {
	/* Returns the column number containing the given cell. */
	int col = cell % getSize();
	return col;
}

int* cells_in_column(int col) {
	/* Returns list of cell indexes in the given column. */
	int *arr = (int *)malloc(getSize() * sizeof(int));
	for (int i = 0; i < getSize(); i++) {
		*(arr + i) = col + i*getSize();
	}
	return arr;
}

int* get_column_values(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in column
	 * `index`. */
	int *col = (int *)malloc(getSize() * sizeof(int));
	for (int i = 0; i < getSize(); i++) {
		*(col + i) = *(cells + index + i*getSize());
	}
	return col;
}

int cell_to_box(int cell) {
	/* Returns the box number containing the given cell. */
	int rt = (int)sqrt(getSize());
	int box = rt*(int)(cell_to_row(cell)/rt) + cell_to_column(cell)/rt;
	return box;
}

int* cells_in_box(int box) {
	/* Returns list of cell indexes in the given box. */
	int *arr = (int *)malloc(getSize() * sizeof(int));
	int root = (int)sqrt(getSize());
	int row = box / root;
	int offset = box % root;
	int base_offset = getSize()*root*row + root*offset;
	for (int i = 0; i < getSize(); i++) {
		*(arr + i) = base_offset + i + (getSize()-root)*(int)(i/root);
	}
	return arr;
}

int* get_box_values(int* cells, int index) {
	/* Returns subset of `cells` matching values contained in box
	 * `index`. */
	int *box = cells_in_box(index);
	for (int i = 0; i < getSize(); i++) {
		*(box + i) = *(cells + *(box + i));
	}
	return box;
}
