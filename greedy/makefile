
CC=g++
O=-O0
BIN=greedy
ULIB=../utils/
DEBUG=-g
W=-Wall
PIPE=

$(BIN): main.cpp fileReader.o randomize.o tools.o $(ULIB)*.h
	$(CC) $(O) $(DEBUG) $(W) $(PIPE) main.cpp fileReader.o randomize.o tools.o -o $(BIN) -I$(ULIB)


fileReader.o: $(ULIB)fileReader.c
	$(CC) $(W) -c $(O) $(DEBUG) $(ULIB)fileReader.c


randomize.o: $(ULIB)randomize.c
	$(CC) $(W) -c $(O) $(DEBUG) $(ULIB)randomize.c


tools.o: $(ULIB)tools.c
	$(CC) $W -c $(O) $(DEBUG) $(ULIB)tools.c


clean: *.o $(BIN)
	rm $(BIN) *.o
