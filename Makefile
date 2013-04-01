SRCDIR=src/
OBJDIR=obj/
INCDIR=include/
MAINDIR=$(SRCDIR)main/

CC=g++
EXEC=Jinn

SRC = $(shell find $(SRCDIR) -name "*.cpp"  ! -path '$(MAINDIR)*')
OBJ = $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRC))
OBJSUBDIR = $(dir $(OBJ))


compile: directory $(OBJ)

Jinn: compile 
	$(CC) -I $(INCDIR) $(OBJ) $(MAINDIR)$@.cpp -o $@ 	


$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) -I $(INCDIR) -c $< -o $@

directory:
	mkdir -p $(OBJSUBDIR)

clean:
	rm -rf $(OBJDIR)
	
rebuild: clean compile	
