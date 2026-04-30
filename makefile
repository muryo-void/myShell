CC = gcc
CFLAGS = -Wall
LIBS = -lreadline
TARGET = myShell

all: $(TARGET)

$(TARGET): src/myShell.c
	$(CC) $(CFLAGS) -o $(TARGET) src/myShell.c $(LIBS)

clean:
	rm -f $(TARGET)