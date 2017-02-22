# Bowei Zhao In Class Assignment # 4
CC = g++

all: run

run: Board.o Checker.o Game.o main.o
	g++ Board.o Checker.o Game.o main.o -o run

main.o: main.cpp
	g++ -Wall -c main.cpp

Game.o: Game.cpp Game.h
	g++ -Wall -c Game.cpp

Checker.o: Checker.cpp Checker.h
	g++ -Wall -c Checker.cpp 

Board.o: Board.cpp Board.h
	g++ -Wall -c Board.cpp


