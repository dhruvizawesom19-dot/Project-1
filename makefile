CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJ = main.o bit.o board.o game.o

all: checkers

checkers: $(OBJ)
	$(CC) $(CFLAGS) -o checkers $(OBJ)

main.o: main.c board.h game.h
	$(CC) $(CFLAGS) -c main.c

bit.o: bit.c bit.h
	$(CC) $(CFLAGS) -c bit.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c

game.o: game.c game.h board.h
	$(CC) $(CFLAGS) -c game.c

clean:
	rm -f *.o checkers
