# Makefile pour Microcosmos

CC = gcc
CPPC = g++
CFLAGS = -Wall -std=c99 -c -D DEBUG
CPPFLAGS = -Wall -c -D DEBUG
LIBS = -lm -lstdc++
PROJECT = Microcosmos
EXE = sim.x

OFILES = main.o error.o sim.o generateur.o particule.o trounoir.o

all: rendu1

rendu1: main.o error.o sim.o generateur.o particule.o trounoir.o
	@echo "\033[32mLinking...\033[0m"
	$(CC) $(OFILES) -o $(EXE) $(LIBS)

main.o: main.cpp 
	@echo "\033[1;32mBuilding\033[21m main.cpp\033[0m"
	$(CPPC) $(CPPFLAGS) $< -o $@

error.o: error.c error.h
	@echo "\033[1;32mBuilding\033[21m error.c\033[0m"
	$(CC) $(CFLAGS) $< -o $@
	
sim.o: sim.c sim.h generateur.h trounoir.h particule.h error.h
	@echo "\033[1;32mBuilding\033[21m sim.c\033[0m"
	$(CC) $(CFLAGS) $< -o $@
	
generateur.o: generateur.c generateur.h error.h
	@echo "\033[1;32mBuilding\033[21m generateur.c\033[0m"
	$(CC) $(CFLAGS) $< -o $@

particule.o: particule.c particule.h error.h
	@echo "\033[1;32mBuilding\033[21m particule.c\033[0m"
	$(CC) $(CFLAGS) $< -o $@
	
trounoir.o: trounoir.c trounoir.h error.h
	@echo "\033[1;32mBuilding\033[21m trounoir.c\033[0m"
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	@echo "\033[33mCleaning...\033[0m"
	-rm *.o
	-rm *.x
	-rm *.out
