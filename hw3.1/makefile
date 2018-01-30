all: main

main: main.o ConnectFour.o
	g++ -std=c++11 main.o ConnectFour.o -o exe

main.o: main.cpp ConnectFour.cpp
	g++ -std=c++11 -c main.cpp ConnectFour.cpp



clean:
	rm *.o exe
