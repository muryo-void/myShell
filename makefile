CC = gcc
CFLAGS = -Wall
TARGET = myShell

all: $(TARGET)

$(TARGET): src/myShell.c
	$(CC) $(CFLAGS) -o $(TARGET) src/myShell.c

clean:
	rm -f $(TARGET)
