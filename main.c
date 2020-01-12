#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"
#include "filemanager.h"
#include "board.h"

#define EMPTY 0

int main(int argc, char** argv)
{
    if (argc == 3)
    {
        int*** board;
        int size;

        /* parse size argument from command-line to integer */
        size = atoi(argv[2]);

        /* create a board of specified size, this will need to be freed */
        board = create_board(size);
        /* read board from file passed in command-line */
        read_board(board, argv[1], size);

        if (solve(board, size))
        {
            #ifndef QUIET
            /* board was solved, display solution */
            display_board(board, size);
            #endif
        }
        else
        {
            /* board could not be solved */
            printf("No solution\n");
        }

        /* free board memory */
        free_board(board, size);
        board = NULL;
    }
    else
    {
        /* incorrect number of arguments */
        printf("Usage: ./solve filename size\n");
    }

    return 0;
}

int solve(int*** board, int size)
{
    int solved, num, row, col;

    row = 0;
    col = 0;
    if (find_empty_space(board, &row, &col, size))
    {
        /* an empty space was found, row and col were updated */
        solved = 0;

        /* iterate through numbers 1 to size while board not solved */ 
        num = 1;
        while (!solved && num < size + 1)
        {
            if (valid_placement(board, row, col, num, size))
            {
                /* can place number in position */

                #ifdef VERBOSE
                printf("%d, %d, %d\n", row, col, num);
                #endif

                /* update board with number in position */
                (*board)[row][col] = num;
                /* call this function */
                solved = solve(board, size);

                if (!solved)
                {
                    /* placing this number did not lead to a solution
                     * so we remove it */
                    (*board)[row][col] = EMPTY;
                }
            }

            /* increment number */
            num++;
        }
    }
    else
    {
        /* no empty places, board must be solved */
        solved = 1;
    }

    return solved;
}

int valid_placement(int*** board, int row, int col, int num, int size)
{
    int found, i, j, r;

    found = 0;

    /* while number not found, check each column in row */
    i = 0;
    while (!found && i < size)
    {
        found = (*board)[row][i] == num;
        i++;
    }

    /* while number not found, check each row in column */
    j = 0;
    while (!found && j < size)
    {
        found = (*board)[j][col] == num;
        j++;
    }

    /* r is the square root of board size */
    r = (int)sqrt(size);

    /* the value of 'i' will be added to row */
    i = 0;
    while (!found && i < r)
    {
        /* the value of 'j' will be added to col */
        j = 0;
        while (!found && j < r)
        {
            /* row - (row % r) is the first row in the box */
            found = (*board)[row - (row % r) + i][col - (col % r) + j] == num;

            j++;
        }

        i++;
    }

    return !found;
}

int find_empty_space(int*** board, int* row, int* col, int size)
{
    int found, i, j;

    /* we haven't found an empty space yet */
    found = 0;

    /* while empty space not found, iterate through 0 to size */
    i = 0;
    while (!found && i < size)
    {
        /* while empty space not found, iterate through 0 to size */
        j = 0;
        while (!found && j < size)
        {
            if ((*board)[i][j] == EMPTY)
            {
                /* position is empty space, set found to true  */
                found = 1;

                /* update imported row and col pointers */
                *row = i;
                *col = j;
            }

            j++;
        }

        i++;
    }

    return found;
}

