
CC=g++
O=-O2
BIN=greedy
ULIB=../utils/
DEBUG=
W=-Wall
PIPE=

all: main.cpp fileReader.o randomize.o tools.o greedy.cpp noname.cpp $(ULIB)*.h
	$(CC) $(O) $(DEBUG) $(W) $(PIPE) main.cpp fileReader.o randomize.o tools.o greedy.cpp noname.cpp -o $(BIN) -I$(ULIB)


fileReader.o: $(ULIB)fileReader.c
	$(CC) $(W) -c $(O) $(DEBUG) $(ULIB)fileReader.c


randomize.o: $(ULIB)randomize.c
	$(CC) $(W) -c $(O) $(DEBUG) $(ULIB)randomize.c


tools.o: $(ULIB)tools.cpp
	$(CC) $W -c $(O) $(DEBUG) $(ULIB)tools.cpp


clean: *.o $(BIN)
	rm $(BIN) *.o
