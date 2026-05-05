/*
 * @author Adrian Pinggera
 * @date 30.04.2026
 * * UI-Update: Startbild, PWD & Commandline, Exit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

// ASCII - Farbcodes
#define GRN "\001\033[1;32m\002"
#define BLU "\001\033[1;34m\002"
#define CYN "\001\033[1;36m\002"
#define YEL "\001\033[1;33m\002"
#define RED "\001\033[1;31m\002"
#define RST "\001\033[0m\002"

// Aktuelle Zeit
void get_time(char *zeit_puffer) {
    time_t raw;
    struct tm *info;
    time(&raw);
    info = localtime(&raw);
    strftime(zeit_puffer, 10, "%H:%M:%S", info);
}

int main() {
    system("clear");
    char *username = getenv("USER");
    if (!username) username = "user";

    // Willkommen-Box
    printf(BLU "╭─────────────────────────────────────────────────── Willkommen zurück, " GRN "%s" BLU "! ───────────────────────────────────────────────────╮\n\n" RST, getenv("USER"));

    // Fastfetch 
    system("fastfetch --config /etc/myShell/config/design.jsonc");

    // Wilkommmen-Box Abschluss
    printf(BLU "\n╰─────────────────────────────────────────────────────────────────────────");
    for(int i = 0; i < strlen(username); i++) printf("─");
    printf("───────────────────────────────────────────────────╯\n" RST);

    char *eingabe;
    char pfad[1024];
    char zeit[10];
    char prompt[2048];

    while (1) {
        if (getcwd(pfad, sizeof(pfad)) == NULL) strcpy(pfad, "?");
        get_time(zeit);

        // Prompt String
        sprintf(prompt, 
                "\n" BLU "╭─" RST " " GRN "👤 %s" RST " │ " CYN "📂 %s" RST " │ " YEL "🕒 %s" RST 
                "\n" BLU "╰─ ❯ " RST, 
                username, pfad, zeit);

        eingabe = readline(prompt);

        if (eingabe == NULL) break;
        if (*eingabe != '\0') add_history(eingabe);

        // Input zerlegen
        char *befehl_args[64];
        int j = 0;
        char *p = strtok(eingabe, " ");
        while (p != NULL && j < 63) {
            befehl_args[j++] = p;
            p = strtok(NULL, " ");
        }
        befehl_args[j] = NULL;

        if (befehl_args[0] == NULL) { 
            free(eingabe); 
            continue; 
        }

        // exit
        if (strcmp(befehl_args[0], "exit") == 0) {
            printf("\n" BLU "╭─" RST " " RED "Session beendet" RST "\n");
            printf(BLU "╰─ ❯" RST " " GRN "Bis bald, %s!" RST "\n\n", username);
            free(eingabe);
            break;
        }

        // cd
        if (strcmp(befehl_args[0], "cd") == 0) {
            if (befehl_args[1]) chdir(befehl_args[1]);
            free(eingabe);
            continue;
        }

        // Ausfuehren
        if (fork() == 0) {
            if (execvp(befehl_args[0], befehl_args) == -1) perror("Fehler");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
        free(eingabe);
    }
    return 0;
}