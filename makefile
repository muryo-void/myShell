CC = gcc
CFLAGS = -Wall
LIBS = -lreadline
TARGET = myShell

all: $(TARGET)

$(TARGET): src/myShell.c
	$(CC) $(CFLAGS) -o $(TARGET) src/myShell.c $(LIBS)

install-deps:
	sudo apt update
	sudo apt install -y libreadline-dev fastfetch

clean:
	rm -f $(TARGET)