########################################################################
# Makefile pour le rendu 1 du projet Microcosmos
# date : 15.03.2015
# version : 1
# Auteur : Minh Truong & Jérémy Jayet
########################################################################

PROJECT = Microcosmos
EXE = rendu2.x

CC = gcc
CFLAGS = -Wall -std=c99 -c -g
CFILES = $(wildcard *.c)

CPPC = g++
CPPFLAGS = -Wall -c -g
CPPFILES = $(wildcard *.cpp)

OFILES = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
LIBS = -lGLU -lGL -lXmu -lXext -lX11 -lXi -lm -lstdc++ -lglut -lglui

all: $(OFILES)
	@echo "\033[1;32mLinking...\033[0m"
	$(CC) $(OFILES) -o $(EXE) $(LIBS)

%.o: %.cpp
	@echo "\033[1;32mBuilding\033[21m $<\033[0m"
	$(CPPC) $(CPPFLAGS) $< -o $@

%.o: %.c
	@echo "\033[1;32mBuilding\033[21m $<\033[0m"
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo "\033[33mCleaning...\033[0m"
	-rm -f *.o *.x *.out *.tmp *.d *.c~ *.h~ *.out~ *.tmp~

depend:
	@echo "\033[33mGenerating dependencies...\033[0m"
	@
	@sed '/^### DEPENDENCIES ###/q' Makefile > Makefile.tmp
	@
	@echo "#-- C rules --#" >> Makefile.tmp
	@sed '/^#-- C rules --#/q' Makefile.tmp > Makefile.tmp2
	@mv Makefile.tmp2 Makefile.tmp
	$(CC) -MM $(CFLAGS) $(CFILES) >> Makefile.tmp
	@
	@echo "#-- C++ rules --#" >> Makefile.tmp
	@sed '/^#-- C++ rules --#/q' Makefile.tmp > Makefile.tmp2
	@mv Makefile.tmp2 Makefile.tmp
	$(CPPC) -MM $(CPPFLAGS) $(CPPFILES) >> Makefile.tmp
	@
	@mv Makefile.tmp Makefile

### DEPENDENCIES ###
#-- C rules --#
error.o: error.c error.h
generateur.o: generateur.c graphic.h error.h constantes.h tolerance.h \
 generateur.h
graphic.o: graphic.c graphic.h constantes.h tolerance.h
particule.o: particule.c graphic.h constantes.h tolerance.h error.h \
 particule.h
sim.o: sim.c particule.h trounoir.h generateur.h error.h constantes.h \
 tolerance.h sim.h
trounoir.o: trounoir.c graphic.h constantes.h tolerance.h error.h \
 trounoir.h
#-- C++ rules --#
main.o: main.cpp sim.h error.h graphic.h
