#include "global.h"

void runcd(char *argu, int arg1, int arg2) {
    if (arg2) {
        fprintf(stderr, "Error: More than one location supplied.\n");
        return;
    }

    if (arg1 == 0) {
        strcpy(argu, tilda);
    }

    if (strcmp(argu, "-") == 0) {
        if (strcmp(previous, "INVALID") == 0) {
            perror("cd: OLDPWD not set\n");
            return;
        } else {
            strcpy(argu, previous);
        }
    } else if (strcmp(argu, "~") == 0) {
        strcpy(argu, tilda);
    }

    getcwd(previous, 100);

    int status = chdir(argu);
    if (status) {
        perror("MISSING LOCATION");
        return;
    }
}