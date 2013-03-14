
CC=gcc
O=-O2
BIN=precise
ULIB=../utils/
PLIB=../planarity/

$(BIN): main.c fileReader.o $(PLIB)*.c $(PLIB)*.h $(ULIB)*.h
	$(CC) $(O) main.c fileReader.o -o $(BIN) $(PLIB)*.c -I$(PLIB) -I$(ULIB)


fileReader.o: $(ULIB)fileReader.c
	$(CC) -c $(O) $(ULIB)fileReader.c


clean: *.o $(BIN)
	rm $(BIN) *.o
