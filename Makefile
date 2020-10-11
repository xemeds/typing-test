# Compiler
CC=gcc

# Target file name
TARGET=typing

all:
	$(CC) typing.c -o $(TARGET)

clean:
	rm $(TARGET)
