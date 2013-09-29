SRCDIR=src/
OBJDIR=obj/
INCDIR=include/
MAINDIR=$(SRCDIR)main/

CC=g++
EXEC=Jinn

SRC = $(shell find $(SRCDIR) -name "*.cpp"  ! -path '$(MAINDIR)*')
OBJ = $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRC))
OBJSUBDIR = $(dir $(OBJ))
DEBUGFLAG=-O2 -Os 
LINK=-lcurses -lpthread -lboost_system -lboost_regex -lm -L/usr/lib/libboost_regex.so
OPTION=-std=c++11
WARNINGFLAG=

ifeq ($(DEBUG),1)
DEBUGFLAG=-g3 -O0 -pg
CC=clang++
endif

ifeq ($(WARNING),1)
WARNINGFLAG=-Wall -Wextra
endif

compile: directory $(OBJ)

Jinn: compile 
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)$@.cpp -o $@ $(LINK) $(DEBUGFLAG) $(WARNINGFLAG)

ClientJinn: compile
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)$@.cpp -o $@ $(LINK) $(DEBUGFLAG) $(WARNINGFLAG)

TestUnitaire: compile
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)$@.cpp -o $@ $(LINK) $(DEBUGFLAG) $(WARNINGFLAG)
	./$@

$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(OPTION) -I $(INCDIR) -c $< -o $@ $(DEBUGFLAG) $(WARNINGFLAG)

directory:
	mkdir -p $(OBJSUBDIR)

clean:
	rm -rf $(OBJDIR)
	
rebuild: clean compile	
