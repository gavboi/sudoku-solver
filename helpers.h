#ifndef HELPERS_H
#define HELPERS_H

int bit_shift(int val);
int bit_flip(int val);

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

#endif
