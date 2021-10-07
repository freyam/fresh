#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

int takeInput(char *str) {
    size_t bufsize = 5000;

    char *buf = malloc(sizeof(char) * 5000);
    getline(&buf, &bufsize, stdin);
    strcpy(str, buf);
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    if (strlen(str)) {
        history_append(str);
        return 1;
    }
    return 0;
}

// turtle happy