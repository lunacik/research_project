
planarity: main.c fileReader.o ../planarity/*.c ../planarity/*.h ../file_reader/*.h
	gcc -O2 main.c fileReader.o -o precise ../planarity/*.c -I../planarity -I../file_reader


fileReader.o: ../file_reader/fileReader.c
	gcc -c -O2 ../file_reader/fileReader.c


clean: *.o precise
	rm precise *.o
