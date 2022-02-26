#!/bin/bash

exercise=$1

cd $exercise

g++ -c $exercise.cpp $exercise.tests.cpp
g++ -o exercise.exe $exercise.o $exercise.tests.o
./exercise.exe

rm exercise.exe $exercise.o $exercise.tests.o
