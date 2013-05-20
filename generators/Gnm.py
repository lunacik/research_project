#!/usr/bin/python3

from sys import argv
from sys import exit
from random import randint
from random import seed
from random import shuffle



if argv.__len__() < 3:
    print("usage: ./generator.py edges_count vertices_count")
    exit(1)

edges_count = int(argv[1])
vertices_count = int(argv[2])

if((vertices_count ** 2 - vertices_count)/2 < edges_count):
    print("impossible graph. too much of edges")
    exit(1)


seed(None)

unused_vertices_list = [index for index in range(vertices_count)]
shuffle(unused_vertices_list)


edges_list = []

if(unused_vertices_list.__len__() % 2 != 0):
    index1 = unused_vertices_list.pop() 
    index2 = randint(0, vertices_count - 1)
    if(index1 > index2):
        edges_list.append((index1, index2))
    else:
        edges_list.append((index2, index1))


while unused_vertices_list != [] and edges_list.__len__() < edges_count:
    index1 = unused_vertices_list.pop()    
    index2 = unused_vertices_list.pop()    
    
    if(index1 > index2):
        edges_list.append((index1, index2))
    else:
        edges_list.append((index2, index1))


while edges_list.__len__() != edges_count:
    index1 = randint(0, vertices_count - 1)
    index2 = randint(0, vertices_count - 1)
    if(index1 == index2): continue
    
    if(index1 > index2):
        if(not edges_list.__contains__((index1, index2))):
            edges_list.append((index1, index2))
    elif not edges_list.__contains__((index2, index1)):
        edges_list.append((index2, index1))



output_file_name = str(edges_count) + "x" + str(vertices_count) + ".txt"
output_file = open(output_file_name, "w")



output_file.write(str(edges_count) + "\n")
output_file.write(str(vertices_count) + "\n")


for u, v in edges_list:
    output_file.write(str(u) + " " + str(v) + "\n")


output_file.close()


