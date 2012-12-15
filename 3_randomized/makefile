
randomized: main.c fileReader.o randomize.o ../planarity/*.c ../planarity/*.h ../file_reader/*.h
	gcc main.c fileReader.o randomize.o -o randomized ../planarity/*.c -I../planarity -I../file_reader -I../rand


fileReader.o: ../file_reader/fileReader.c
	gcc -c ../file_reader/fileReader.c


randomize.o: ../rand/randomize.c
	gcc -c ../rand/randomize.c


clean: *.o randomized
	rm randomized *.o
