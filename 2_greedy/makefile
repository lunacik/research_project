
greedy: main.c fileReader.o randomize.o ../planarity/*.c ../planarity/*.h ../file_reader/*.h
	gcc -O2 main.c fileReader.o randomize.o -o greedy ../planarity/*.c -I../planarity -I../file_reader -I../rand


fileReader.o: ../file_reader/fileReader.c
	gcc -c -O2 ../file_reader/fileReader.c


randomize.o: ../rand/randomize.c
	gcc -c -O2 ../rand/randomize.c


clean: *.o greedy
	rm greedy *.o
