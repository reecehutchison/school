COMPILER = g++
TARGET = main
SRC = main.cpp TreeNode.cpp
VERSION = -std=c++17

all: $(TARGET) 

$(TARGET): $(SRC)
	$(COMPILER) $(SRC) -o $(TARGET) $(VERSION) 

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)