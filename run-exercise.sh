#!/bin/bash

cd find-center-of-star-graph

g++ -c find-center-of-star-graph.cpp find-center-of-star-graph.tests.cpp
g++ -o exercise.exe find-center-of-star-graph.o find-center-of-star-graph.tests.o
./exercise.exe

rm exercise.exe find-center-of-star-graph.o find-center-of-star-graph.tests.o

