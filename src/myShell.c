/*
 * @author Adrian Pinggera
 * @date 30.04.2026
 *
 * Prompt Design & aktuelles Arbeitsverzeichnis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Farbcodes
#define GRN "\033[1;32m"
#define BLU "\033[1;34m"
#define RST "\033[0m"

int main() {
    char input[1024];
    char *args[64];
    char *token;
    char cwd[1024];

    // Username
    char *user = getenv("USER");
    if (user == NULL) {
        user = "user"; 
    }

    while (1) {
        // Aktuelles Arbeitsverzeichnis
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            strcpy(cwd, "?");
        }

        // nutzer@shell: /ordner/ $
        printf("%s%s@shell%s:%s%s%s$ ", GRN, user, RST, BLU, cwd, RST);
        fflush(stdout);

        // Zeile einlesen
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Enter-Taste (\n) am Ende entfernen
        input[strcspn(input, "\n")] = '\0';

        // Befehl zerlegen
        int i = 0;
        token = strtok(input, " ");
        while (token != NULL && i < 63) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Falls nichts eingegeben wurde
        if (args[0] == NULL) continue;

        // Beenden
        if (strcmp(args[0], "exit") == 0) {
            printf("Logout...\n");
            break;
        }

        // Verzeichnis wechseln
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] != NULL) {
                if (chdir(args[1]) != 0) {
                    perror("cd Fehler");
                }
            }
            continue;
        }

        // Programm ausführen
        pid_t pid = fork();
        if (pid == 0) {
            // Kindprozess
            if (execvp(args[0], args) == -1) {
                perror("Fehler beim Ausführen");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Fork fehlgeschlagen");
        } else {
            wait(NULL);
        }
    }

    return 0;
}