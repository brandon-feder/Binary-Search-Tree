#!/bin/bash

gcc ./src/main.cpp -o ./bin/main  -lstdc++;
./bin/main Movies.txt;
rm ./bin/main;
