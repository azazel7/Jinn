SRCDIR=src/
OBJDIR=obj/
INCDIR=include/
MAINDIR=$(SRCDIR)main/

CC=g++
EXEC=Jinn

SRC = $(shell find $(SRCDIR) -name "*.cpp"  ! -path '$(MAINDIR)*')
OBJ = $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRC))
OBJSUBDIR = $(dir $(OBJ))
FLAG= -std=c++11 -lcurses -lpthread -lboost_system
OPTION=-g

compile: directory $(OBJ)

Jinn: compile 
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)$@.cpp -o $@ $(FLAG)

ClientJinn: compile
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)$@.cpp -o $@ $(FLAG)

TestUnitaire: compile
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)$@.cpp -o $@ $(FLAG)
	./$@

$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(OPTION) -I $(INCDIR) -c $< -o $@ $(FLAG)

directory:
	mkdir -p $(OBJSUBDIR)

clean:
	rm -rf $(OBJDIR)
	
rebuild: clean compile	
