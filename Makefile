all: main.bin
main.bin: main.o
	g++  -std=c++11 -o main.bin main.o
main.o: main.cpp
	g++  -std=c++11 -c main.cpp