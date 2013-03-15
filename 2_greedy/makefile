
CC=gcc
O=-O0
BIN=greedy
ULIB=../utils/
PLIB=../planarity/
#PLIB=/home/lunacik/planarity-read-only/c/
DEBUG=-g
W=-Wall

$(BIN): main.c fileReader.o randomize.o tools.o $(PLIB)*.c $(PLIB)*.h $(ULIB)*.h
	$(CC) $(O) $(DEBUG) $(W) main.c fileReader.o randomize.o tools.o -o $(BIN) $(PLIB)*.c -I$(PLIB) -I$(ULIB)


fileReader.o: $(ULIB)fileReader.c
	$(CC) $(W) -c $(O) $(DEBUG) $(ULIB)fileReader.c


randomize.o: $(ULIB)randomize.c
	$(CC) $(W) -c $(O) $(DEBUG) $(ULIB)randomize.c


tools.o: $(ULIB)tools.c $(PLIB)
	$(CC) $W -c $(O) $(DEBUG) $(ULIB)tools.c -I$(PLIB)


clean: *.o $(BIN)
	rm $(BIN) *.o
