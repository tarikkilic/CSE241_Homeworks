all: main

main: main.o GTUSet.o GTUMap.o
	g++ -std=c++11 main.o GTUSet.o GTUMap.o -o exe

main.o: main.cpp GTUSet.cpp GTUMap.cpp
	g++ -std=c++11 -c main.cpp GTUSet.cpp GTUMap.cpp



clean:
	rm *.o exe
