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

# Installiert das Programm 
install: $(TARGET)
	@echo "Installiere $(TARGET) nach /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/$(TARGET)
	sudo chmod +x /usr/local/bin/$(TARGET)
	@echo "Kopiere Konfiguration nach /etc/myShell..."
	sudo mkdir -p /etc/myShell
	sudo cp -r config/* /etc/myShell/
	@echo "Installation abgeschlossen!"

# Entfernt das Programm 
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	sudo rm -rf /etc/myShell
	@echo "$(TARGET) wurde erfolgreich deinstalliert."

clean:
	rm -f $(TARGET)