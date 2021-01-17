FILES = src/main.c src/opcodes.c
CLIBS = -w -lSDL2
CC = gcc

main: $(FILES)
	$(CC) $(FILES) $(CLIBS) -o main

run: main
	./main

clean:
	rm -rf ./main
