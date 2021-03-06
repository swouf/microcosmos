########################################################################
# \file Makefile
# \brief Makefile pour le rendu 3 du projet Microcosmos
# \date 17.05.2015
# \version : 3
# \author : Minh Truong & Jérémy Jayet
########################################################################

PROJECT = Microcosmos
EXE = sim.x

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
