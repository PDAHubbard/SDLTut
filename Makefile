#OBJS specs which files to compile as part of the project
OBJS = 01_hello_SDL.cpp

#OBJ_NAME is the name of the executable
OBJ_NAME = 01_hello_SDL

#CC is the name of the compiler
CC = g++

#COMPILER FLAGS are the compiler flags
#-w suppresses all warnings
COMPILER_FLAGS = -Wall -Wextra -pedantic

#LINKER_FLAGS specifies the libraries to link/load
LINKER_FLAGS = -lSDL2 -lSDL2_image

#Target to compile the executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

