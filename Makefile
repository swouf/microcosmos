# Makefile pour Microcosmos

CC = gcc
CFLAGS = -Wall -std=c99 -c -D DEBUG
CFILES = sim.c generateur.c particule.c trounoir.c error.c

CPPC = g++
CPPFLAGS = -Wall -c -D DEBUG
CPPFILES = main.cpp

LIBS = -lm -lstdc++
PROJECT = Microcosmos
EXE = rendu1.x

OFILES = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

all: rendu1

rendu1: $(OFILES)
	@echo "\033[32mLinking...\033[0m"
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
	@cat Makefile > Makefile.tmp
	@echo "#-- C rules --#" >> Makefile.tmp
	@sed '/^#-- C rules --#/q' Makefile.tmp > Makefile.tmp2
	@mv Makefile.tmp2 Makefile.tmp
	$(CC) -MM $(CFLAGS) $(CFILES) >> Makefile.tmp
	@echo "#-- C++ rules --#" >> Makefile.tmp
	@sed '/^#-- C++ rules --#/q' Makefile.tmp > Makefile.tmp2
	@mv Makefile.tmp2 Makefile.tmp
	$(CPPC) -MM $(CPPFLAGS) $(CPPFILES) >> Makefile.tmp
	@mv Makefile.tmp Makefile

### DEPENDENCIES ###
