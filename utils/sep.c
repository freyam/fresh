#include "global.h"

void commandsep(char *argu) {
    int count = 0;
    char *commands[100];
    char *ptr = strtok(argu, ";");
    while (ptr != NULL) {
        commands[count++] = ptr;
        ptr = strtok(NULL, ";");
    }
    for (int i = 0; i < count; i++) {
        execute_pipe(commands[i]);
    }
}