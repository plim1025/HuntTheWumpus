CC = g++
exe_file = HuntTheWumpus
$(exe_file): game.o room.o event.o wumpus.o bats.o pit.o gold.o prog.o
	$(CC) -g -std=c++11 game.o room.o event.o wumpus.o bats.o pit.o gold.o prog.o -o $(exe_file)
game.o: game.cpp
	$(CC) -c game.cpp
room.o: room.cpp
	$(CC) -c room.cpp
event.o: event.cpp
	$(CC) -c event.cpp
wumpus.o: wumpus.cpp
	$(CC) -c wumpus.cpp
bats.o: bats.cpp
	$(CC) -c bats.cpp
pit.o: pit.cpp
	$(CC) -c pit.cpp
gold.o: gold.cpp
	$(CC) -c gold.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp
clean:
	rm -f *.out *.o *.gch *.d $(exe_file)

