/*
 * @author Adrian Pinggera
 * @date 30.04.2026
 *
 * Update: Implementierung des Built-in Befehls 'cd' mittels chdir().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char input[1024];
    char *args[64];
    char *token;

    while (1) {
        printf("myShell> ");
        fflush(stdout);

        // Befehl einlesen
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Zeilenumbruch entfernen
        input[strcspn(input, "\n")] = '\0';

        // Befehl in *args[] speichern
        int j = 0;
        token = strtok(input, " ");
        while (token != NULL && j < 63) {
            args[j] = token;
            j++;
            token = strtok(NULL, " ");
        }
        args[j] = NULL;

        // Leere Eingabe prüfen
        if (args[0] == NULL) {
            continue;
        }

        // --- Spezialfälle  ---

        // exit
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // cd 
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "myShell: Pfad für 'cd' fehlt\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("myShell");
                }
            }
            continue;
        }

        // --- Befehl ausführen ---
        pid_t pid = fork();

        if (pid == 0) {
            // Kindprozess
            if (execvp(args[0], args) == -1) {
                perror("Fehler beim Ausführen");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Fehler bei fork
            perror("Fork fehlgeschlagen");
        } else {
            // Elternprozess
            wait(NULL);
        }
    }

    printf("Shell beendet.\n");
    return 0;
}