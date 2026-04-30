CC = gcc
CFLAGS = -Wall
TARGET = kleineShell

all: $(TARGET)

$(TARGET): src/kleineShell.c
	$(CC) $(CFLAGS) -o $(TARGET) src/kleineShell.c

clean:
	rm -f $(TARGET)