
CC=g++
O=-O2
BIN=test
LIB=../greedy
DEBUG=
W=-Wall
PIPE=-std=gnu++11
UNITLIB=boost_unit_test_framework

all: *.cpp
	$(CC) *.cpp -o $(BIN) -l$(UNITLIB)
	./$(BIN)

clean: *.o $(BIN)
	rm $(BIN) *.o
