PROG = SortingExec

OBJS = src/utils/stopwatch.cpp src/utils/vecgen.cpp src/algorithms/sortingalgorithms.cpp

all:
	g++ src/main.cpp $(OBJS) -o $(PROG) -std=c++17 -lncurses 

run: all
	./$(PROG)
