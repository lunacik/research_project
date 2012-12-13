
planarity: main.c fileReader.o ../planarity/*.c ../planarity/*.h ../file_reader/*.h
	gcc -O2 main.c fileReader.o randomize.o -o greedy ../planarity/*.c -I../planarity -I../file_reader -I../rand


fileReader.o: ../file_reader/fileReader.c ../file_reader/fileReader.h
	gcc -c -O2 ../file_reader/fileReader.c -I../file_reader

randomize.o: ../rand/randomize.c ../rand/randomize.h
	gcc -c -O2 ../rand/randomize.c -I../rand


clean: *.o greedy
	rm greedy *.o
