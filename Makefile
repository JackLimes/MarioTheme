.DEFAULT_GOAL=mario
CXX=g++
STD=-std=c++17
FLAGS=-Wall
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

entity.o: entity.h entity.cpp
	${CXX} -c ${STD} ${FLAGS} ${LIBS} entity.cpp

game.o: game.h game.cpp entity.o
	${CXX} -c ${STD} ${FLAGS} ${LIBS} game.cpp

main.o: main.cpp game.o
	${CXX} -c ${STD} ${FLAGS} ${LIBS} main.cpp

mario: main.o game.o
	${CXX} ${STD} ${FLAGS} ${LIBS} entity.o game.o main.o -o mario

.PHONY: clean
clean:
	rm -f *.o mario