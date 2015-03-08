# Makefile pour Microcosmos

CC = gcc
CPPC = g++
CFLAGS = -Wall -c
LIBS = -lm
PROJECT = Microcosmos
EXE = microcosmos.x

OFILES = main.o error.o sim.o generateur.o particule.o trounoir.o

all: rendu1

rendu1: main.o error.o sim.o generateur.o particule.o trounoir.o
	@echo "\033[32mLinking...\033[0m"
	$(CC) $(OFILES) -o $(EXE) $(LIBS)

main.o: main.cpp
	@echo "\033[1;32mBuilding\033[21m main.cpp\033[0m"
	$(CPPC) $(CFLAGS) main.cpp -o main.o

error.o: error.c error.h
	@echo "\033[1;32mBuilding\033[21m error.c\033[0m"
	$(CC) $(CFLAGS) error.c -o error.o
	
sim.o: sim.c sim.h
	@echo "\033[1;32mBuilding\033[21m sim.c\033[0m"
	$(CC) $(CFLAGS) sim.c -o sim.o
	
generateur.o: generateur.c generateur.h
	@echo "\033[1;32mBuilding\033[21m generateur.c\033[0m"
	$(CC) $(CFLAGS) generateur.c -o generateur.o

particule.o: particule.c particule.h
	@echo "\033[1;32mBuilding\033[21m particule.c\033[0m"
	$(CC) $(CFLAGS) particule.c -o particule.o
	
trounoir.o: trounoir.c trounoir.h
	@echo "\033[1;32mBuilding\033[21m trounoir.c\033[0m"
	$(CC) $(CFLAGS) trounoir.c -o trounoir.o
	
clean:
	@echo "\033[33mCleaning...\033[0m"
	-rm *.o 2> cleaning_error.out
	-rm *.x 2> cleaning_error.out
	-rm *.out
