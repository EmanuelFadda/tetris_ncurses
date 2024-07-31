all: main run

main: main.o game.o block.o menu.o leaderboard.o utilities.o
	g++ -o main main.o game.o block.o menu.o leaderboard.o utilities.o -lncurses
	rm -f *.o
	
all_done: 
	rm -f main.exe
	g++ -c main.cpp
	g++ -c game.cpp
	g++ -c block.cpp
	g++ -c menu.cpp
	g++ -c leaderboard.cpp
	g++ -c utilities.cpp
	g++ -c tutorial.cpp
	g++ -o main main.o game.o block.o menu.o leaderboard.o utilities.o tutorial.o -lncurses
	rm *.o
	
main.o: main.cpp
	g++ -c main.cpp

game.o: game.cpp
	g++ -c game.cpp

block.o: block.cpp
	g++ -c block.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

leaderboard.o: leaderboard.cpp
	g++ -c leaderboard.cpp

utilities.o: utilities.cpp
	g++ -c utilities.cpp	

run:
	./main

clean:
	rm -f *.o