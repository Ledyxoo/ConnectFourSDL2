CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = ConnectFour

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)

.PHONY: all clean
