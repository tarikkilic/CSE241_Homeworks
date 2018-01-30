all: main

main: main.o 
	g++ -std=c++11 main.o Cell.o ConnectFourDiag.o ConnectFourUndo.o ConnectFourPlus.o ConnectFourAbstract.o  -o exe

main.o: main.cpp 
	g++ -std=c++11 -c main.cpp Cell.cpp ConnectFourDiag.cpp ConnectFourUndo.cpp  ConnectFourPlus.cpp ConnectFourAbstract.cpp



clean:
	rm *.o exe
