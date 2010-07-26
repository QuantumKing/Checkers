CC = g++ -Wall -ansi
SOURCE = *.cpp
FLAGS = -lGL -lGLU `sdl-config --cflags --libs`
BINARY = 3DCheckers

all:
	$(CC) $(SOURCE) -o $(BINARY) $(FLAGS)

clean:
	@echo Cleaning up...
	@rm $(BINARY)
	@echo Done.
