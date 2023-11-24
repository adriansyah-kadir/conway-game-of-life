CC = gcc
OUT = ./build/main
LDFLAGS = -lncurses

run: main
	$(OUT)

main: main.c
	$(CC) $(LDFLAGS) main.c -o $(OUT)
