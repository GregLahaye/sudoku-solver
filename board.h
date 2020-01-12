#ifndef BOARD_H
#define BOARD_H

int*** create_board(int size);
void free_board(int*** board, int size);
void display_board(int*** board, int size);

#endif

