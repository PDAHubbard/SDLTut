#OBJS specs which files to compile as part of the project
OBJS = 01_hello_SDL.cpp

#OBJ_NAME is the name of the executable
OBJ_NAME = 01_hello_SDL

#Target to compile the executable
all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)

