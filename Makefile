CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -std=c89 -g
OBJ = main.o filemanager.o board.o
EXEC = solve

ifdef VERBOSE
	CFLAGS += -D VERBOSE=1
endif

ifdef QUIET
	CFLAGS += -D QUIET=1
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -lm -o $(EXEC)

main.o : main.c main.h
	$(CC) main.c -c $(CFLAGS)

board.o : board.c board.h
	$(CC) board.c -c $(CFLAGS)

filemanager.o : filemanager.c filemanager.h
	$(CC) filemanager.c -c $(CFLAGS)

clean :
	rm -f $(EXEC) $(OBJ)

