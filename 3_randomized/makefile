
O=-O2
BIN=randomized
ULIB=../utils/
PLIB=../planarity/

$(BIN): main.c fileReader.o randomize.o $(PLIB)*.c $(PLIB)*.h $(ULIB)*.h
	$(CC) $(O) main.c fileReader.o randomize.o -o $(BIN) $(PLIB)*.c -I$(PLIB) -I$(ULIB)


fileReader.o: $(ULIB)fileReader.c
	$(CC) $(O) -c $(ULIB)fileReader.c


randomize.o: $(ULIB)randomize.c
	$(CC) $(O) -c $(ULIB)randomize.c

#.PHONY:
clean: *.o $(BIN)
	rm $(BIN) *.o
