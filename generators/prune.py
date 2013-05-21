#!/usr/bin/python3

import sys


inputFileName = sys.argv[1]
outputFileName = sys.argv[2]

#IN
inputFile = open(inputFileName, "r")
inputFile.readline() #edges count
vertex_count = inputFile.readline()


l = [i[:i.__len__() - 1].split(" ") for i in inputFile.readlines()]
inputFile.close()


#PROC
adj_list = {}

for pair in l:
    if(adj_list.__contains__(pair[0])):
        adj_list[pair[0]].append(pair[1])
    else:
        adj_list[pair[0]] = []
        adj_list[pair[0]].append(pair[1])
 
    if(adj_list.__contains__(pair[1])):
        adj_list[pair[1]].append(pair[0])
    else:
        adj_list[pair[1]] = []
        adj_list[pair[1]].append(pair[0])


def prune(graph, v):
    u = graph[v][0]
    graph[v].remove(u)
    graph[u].remove(v)
    if(graph[u].__len__() == 1):
        prune(graph, u)


for k, v in adj_list.items():
    if(v.__len__() == 1):
        prune(adj_list, k)




def join(graph, v):
    u, k = graph[v]
    if(not graph[u].__contains__(k)):
        graph[u].append(k)
        graph[k].append(u)
        graph[u].remove(v)
        graph[k].remove(v)
        graph[v].clear()
        if(graph[u].__len__() == 2):
            join(graph, u)
        elif(graph[k].__len__() == 2):
            join(graph, k)


for k, v in adj_list.items():
    if(v.__len__() == 2):
        join(adj_list, k)



degree = 0

for _, v in adj_list.items():
    if v.__len__() > degree:
        degree = v.__len__()



for k, v in adj_list.items():
    for i in v:
        if(adj_list[i].__contains__(k)):
            adj_list[i].remove(k)



adj_list = {k : v for k, v in adj_list.items() if v}


#OUT
outputFile = open(outputFileName, "w")

ec = 0
for v in adj_list.values(): ec += v.__len__()

outputFile.write(str(ec) + "\n")
outputFile.write(vertex_count)

for adj in adj_list:
    outputFile.write(adj + " ")
    for a in adj_list[adj]:
        outputFile.write(a + " ")
    outputFile.write("-1\n")


outputFile.write("-2\n")
outputFile.write(str(degree))
outputFile.close()


