#include "global.h"

void RUN_echo(char *argu) {
    char *PTR = NULL;
    char *str = strdup(argu);

    char *token = strtok_r(str, " \t", &PTR);

    token = strtok_r(NULL, " \t", &PTR);
    while (token != NULL) {
        printf("%s ", token);
        token = strtok_r(NULL, " \t", &PTR);
    }
    printf("\n");
}

// turtle happy