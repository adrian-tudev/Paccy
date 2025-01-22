CC = gcc
OUT = paccy
src = src
sdl_flags = -Llib -lmingw32 -lSDL3 -lSDL3_image 
include = -Iinclude
flags = -Wall -g
all:
	$(CC)	$(src)/* -o bin/$(OUT) $(sdl_flags) $(flags) $(include)
