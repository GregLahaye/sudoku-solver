#include <stdlib.h>
#include <stdio.h>

#include "filemanager.h"

void read_board(int*** board, char* filename, int size)
{
    FILE* f;

    /* open file for reading */
    f = fopen(filename, "r");

    if (f != NULL)
    {
        /* file was opened successfully */

        int num, row, col;

        for (row = 0; row < size; row++)
        {
            for (col = 0; col < size; col++)
            {
                /* read value from file */
                fscanf(f, "%d", &num);
                /* update board with read value */
                (*board)[row][col] = num;
            }
        }

        /* close file */
        fclose(f);
    }
    else
    {
        /* file could not be opened */
        perror("Couldn't open file");
    }
}

