CC = gcc
FLAGS = -Wall -Wextra
DIS = src/dispatcher.c -o bin/dispatcher
PROG = src/prog.c -o bin/prog
SRC = ""

all:
	mkdir -p bin
	$(CC) $(FLAGS) $(SRC) $(DIS)
	$(CC) $(FLAGS) $(PROG)

run: all
	./bin/dispatcher

clean:
	rm ./bin/*