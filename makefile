FLAGS = -g -Wall -Wextra -std=gnu11
VFLAGS = --track-origins=yes --malloc-fill=0x40 --leak-check=full --show-leak-kinds=all

all: teque

kitten: teque.c
	gcc $(FLAGS) teque.c -o teque

run: teque
	./teque

valgrind: teque
	valgrind $(VFLAGS) ./teque