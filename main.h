#ifndef MAIN_H
#define MAIN_H

int valid_placement(int*** board, int row, int col, int num, int size);
int solve(int*** board, int size);
int find_empty_space(int*** board, int* row, int* col, int size);

#endif

