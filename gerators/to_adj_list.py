#!/usr/bin/python3


import sys


fileName = sys.argv[1]

file = open(fileName, "r")
edges_count = file.readline()

l = [i[:i.__len__() - 1].split(" ") for i in file.readlines()]



adj_list = {}

uniq_vertices = []

for pair in l:
    if(adj_list.__contains__(pair[0])):
        adj_list[pair[0]].append(pair[1])
    else:
        adj_list[pair[0]] = []
        adj_list[pair[0]].append(pair[1])
    
    if(pair[0] not in uniq_vertices):
        uniq_vertices.append(pair[0])
    if(pair[1] not in uniq_vertices):
        uniq_vertices.append(pair[1])



file = open(sys.argv[2], "w")

file.write(edges_count)

file.write(str(uniq_vertices.__len__()) + "\n")

for adj in adj_list:
    file.write(adj + " ")
    for a in adj_list[adj]:
        file.write(a + " ")
    file.write("-1\n")



