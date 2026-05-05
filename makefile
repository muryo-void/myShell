CC = gcc
CFLAGS = -Wall
LIBS = -lreadline
TARGET = myShell

all: $(TARGET)

$(TARGET): src/myShell.c
	$(CC) $(CFLAGS) -o $(TARGET) src/myShell.c $(LIBS)

install-deps:
	echo "Installiere Abhängigkeiten..."
	sudo apt update
	sudo apt install -y libreadline-dev fastfetch fonts-noto-color-emoji
	@echo "Abhängigkeiten installiert. Eventuell Terminal neu starten!"

# Installiert das Programm 
install: $(TARGET)
	@echo "Installiere Programm..."
	sudo cp $(TARGET) /usr/local/bin/$(TARGET)
	sudo chmod +x /usr/local/bin/$(TARGET)
	
	@echo "Erstelle Konfigurations-Struktur..."
	# Erstellt den Ordner UND den Unterordner config
	sudo mkdir -p /etc/myShell/config
	
	@echo "Kopiere Dateien..."
	sudo cp config/design.jsonc /etc/myShell/config/
	sudo cp config/ascii.txt /etc/myShell/config/
	@echo "Installation fertig!"

# Entfernt das Programm 
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	sudo rm -rf /etc/myShell
	@echo "$(TARGET) wurde erfolgreich deinstalliert."

clean:
	rm -f $(TARGET)