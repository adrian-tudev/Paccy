CC = gcc
OUT = chillguy
src = src
sdl_flags = -lSDL2 -lSDL2_image 
include = -Iinclude
flags = -Wall

all:
	$(CC)	$(src)/* -o bin/$(OUT) $(sdl_flags) $(flags) $(include)
