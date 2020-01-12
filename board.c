#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int*** create_board(int size)
{
    int*** board;
    int i;

    /* allocate memory for pointer to board */
    board = (int***)malloc(sizeof(int**));
    /* allocate memory for each row */
    *board = (int**)malloc(sizeof(int*) * size);

    for (i = 0; i < size; i++)
    {
        /* allocate memory for columns in row */
        (*board)[i] = (int*)malloc(sizeof(int) * size);
    }

    return board;
}

void free_board(int*** board, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        /* free row */
        free((*board)[i]);
    }
    
    /* free board */
    free(*board);
    /* free board pointer */
    free(board);
}

void display_board(int*** board, int size)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%2d ", (*board)[i][j]);
        }
        printf("\n");
    }
}

