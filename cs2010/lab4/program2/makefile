PROG = gameoflife

all:
	g++ main.cpp helpers.cpp -o $(PROG) -std=c++17 -lncurses 

run: all
	./$(PROG)

clean: 
	rm $(PROG)
