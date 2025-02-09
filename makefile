CC = gcc
OUT = paccy
src = src
sdl_flags = -Lvendor/SDL3/lib -lmingw32 -lSDL3 -lSDL3_image 
include = -Iinclude -Ivendor/SDL3
flags = -w -g
all:
	$(CC)	$(src)/* -o bin/$(OUT) $(sdl_flags) $(flags) $(include)
