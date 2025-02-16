PROG = SortingExec

OBJS = src/display/prgdisplay.cpp src/utils/stopwatch.cpp \
	   src/utils/vecgen.cpp

all:
	g++ src/main.cpp $(OBJS) -o $(PROG) -std=c++17 -lncurses 

run: all
	./$(PROG)
