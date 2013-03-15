
CC=gcc
O=-O2
BIN=precise
ULIB=../utils/
PLIB=../planarity/
#PLIB=/home/lunacik/planarity-read-only/c/
DEBUG=


$(BIN): main.c fileReader.o tools.o $(PLIB)*.c $(PLIB)*.h $(ULIB)*.h
	$(CC) $(O) main.c fileReader.o tools.o -o $(BIN) $(PLIB)*.c -I$(PLIB) -I$(ULIB)


fileReader.o: $(ULIB)fileReader.c
	$(CC) -c $(O) $(ULIB)fileReader.c


tools.o: $(ULIB)tools.c $(PLIB)
	$(CC) $W -c $(O) $(DEBUG) $(ULIB)tools.c -I$(PLIB)


clean: *.o $(BIN)
	rm $(BIN) *.o
