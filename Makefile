#using gcc compiler
CC = gcc

#output path and filename
BINARY = ./build/8puzzle

#sources directory
SRC = source/main.c source/game.c source/board.c source/queue.c

#includes directory
INCLUDES = ./includes

#libraries and flags
LIBS = -lm
FLAGS = -g 

all: compile run

compile:
	$(CC) -o $(BINARY) -I$(INCLUDES) $(SRC) $(LIBS)

run:
	$(BINARY)

clean:
	rm *.o