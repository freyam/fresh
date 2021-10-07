#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

void command_separator(char *argu) {
    int count = 1;
    int n = strlen(argu);
    for (int i = 0; argu[i] != '\0'; i++) {
        if (argu[i] == ';' && i != n - 1)
            count++;
    }
    char commands[count][100];
    for (int i = 0; i < count; i++)
        memset(commands[i], '\0', 100 * sizeof(char));
    int c = 0;
    int len = 0;
    for (int i = 0; argu[i] != '\0'; i++) {
        if (argu[i] != ';')
            commands[c][len++] = argu[i];
        else {
            len = 0;
            c++;
        }
    }
    for (int i = 0; i < count; i++)
        command_executor(commands[i]);
}

// void command_separator2(char *argu) { // for repeat
//     char *saveptr = NULL;
//     char *str = strdup(argu);
//     char **token = (char **)malloc(sizeof(char *) * (100));
//     int count = 2;
//     token[0] = strdup(strtok_r(str, " \t", &saveptr));
//     // int count = atoi(strtok_r(NULL, " ", &saveptr));
//     command_executor(strtok_r(NULL, "", &saveptr));
//     printf("\n");
// }

// turtle happy