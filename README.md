# Dijkstra's Algorithm - COP 4530 Project

## This project implements Dijkstra's Algorithm to compute the shortest path between two vertices in an undirected weighted graph using only C++ standard library classes vector and string.

Features:

Graph representation using an adjacency list

Custom Edge and Vertex structures

Dynamic vertex and edge management

Shortest path calculation using a custom min-heap (HeapQueue) and Dijkstra's algorithm

Two test graphs included: one numeric, one campus-based


***Graph.hpp***         - Graph class interface with Edge and Vertex structures

***Graph.cpp***          - Full implementation of the Graph class

***HeapQueue.hpp***      - Custom min-heap (priority queue) template

***main.cpp***           - Main driver with two test graphs<br>&nbsp;<br>

**Compile with C++17:** g++ -std=c++17 main.cpp Graph.cpp
