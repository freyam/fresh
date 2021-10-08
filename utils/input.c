#include "global.h"

int takeInput(char *str) {

    size_t buffersize = 2000; // take input

    if (getline(&buf, &buffersize, stdin) == -1) {
        exit(0);
    }
    if (strlen(buf) != 0) {
        strcpy(str, buf);
        int slen = strlen(str);
        str[slen - 1] = '\0';

        return 1;
    }
    return 0;
}
