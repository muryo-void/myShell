/*
 * @author Adrian Pinggera
 * @date 30.04.2026
 *
 * Pfeiltasten- & Tabcompletion-Support mit readline
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#define GRN "\033[1;32m"
#define BLU "\033[1;34m"
#define RST "\033[0m"

int main() {
    char *input;
    char *args[64];
    char *token;
    char cwd[1024];
    char prompt[2048];

    char *user = getenv("USER");
    if (user == NULL) user = "user";

    while (1) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) strcpy(cwd, "?");
        snprintf(prompt, sizeof(prompt), "%s%s@shell%s:%s%s%s$ ", GRN, user, RST, BLU, cwd, RST);

        input = readline(prompt);

        // History
        if (*input != '\0') {
            add_history(input);
        }

        // Befehl in args zerlegen
        int i = 0;
        token = strtok(input, " ");
        while (token != NULL && i < 63) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            free(input);
            continue;
        }

        // exit
        if (strcmp(args[0], "exit") == 0) {
            free(input);
            printf("Ciao!\n");
            break;
        }

        // cd
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] != NULL) {
                if (chdir(args[1]) != 0) {
                    perror("cd Fehler");
                }
            }
            free(input);
            continue;
        }

        // Programm ausführen
        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Fehler beim Ausführen");
            }
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
        
        free(input);
    }

    return 0;
}