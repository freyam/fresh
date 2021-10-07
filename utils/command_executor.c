#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

void command_executor(char *str) {

    if (strcmp(str, "") == 0) {
        return;
    }

    char *og_str = strdup(str);

    char mycommands[8][100];

    strcpy(mycommands[0], "cd");
    strcpy(mycommands[1], "pwd");
    strcpy(mycommands[2], "ls");
    strcpy(mycommands[3], "exit");
    strcpy(mycommands[4], "echo");
    strcpy(mycommands[5], "history");
    strcpy(mycommands[6], "pinfo");
    strcpy(mycommands[7], "repeat");

    char *arguments[100] = {'\0'};
    char *ptr = strtok(str, " ");
    int j = -1;
    for (int i = 0; i < 8; i++) {
        if (strcmp(ptr, mycommands[i]) == 0) {
            j = i;
            break;
        }
    }
    int c = 1;
    int len = 0;
    while (ptr != NULL) {

        arguments[len++] = ptr;
        if (arguments[len - 1][0] == '~') {
            char temp[1000];
            strcpy(temp, tilda);
            strcat(temp, arguments[len - 1] + 1);
            arguments[len - 1] = temp;
        }
        ptr = strtok(NULL, " ");
    }
    int arg1 = 1, arg2 = 1, pid = -1;
    int pdd, mode = -1;
    int num = 10;
    if (len == 1) {
        if (j == 0) {
            arguments[1] = tilda;
            len++;
        }
        if (j == 4) {
            arguments[1] = "";
            len++;
        }
        pid = -1;
        arg1 = 0;
        arg2 = 0;
    } else if (len == 2) {
        if (j == 5) {
            sscanf(arguments[1], "%d", &num);
        }
        sscanf(arguments[1], "%d", &pid);
        arg2 = 0;
    }

    int bg = 0;
    if (!strcmp(arguments[len - 1], "&")) {
        arguments[len - 1] = '\0';
        bg = 1;
    }
    arguments[len] = '\0';
    switch (j) {
    case 0:
        RUN_cd(arguments[1], arg1, arg2);
        break;
    case 1:
        RUN_pwd();
        break;
    case 2:
        RUN_ls(arguments[1], arguments[2], arg1, arg2);
        break;
    case 3:
        exit(0);
        break;
    case 4:
        RUN_echo(og_str);
        break;
    case 5:
        show_history(num);
        break;
    case 6:
        callpinfo(pid);
        break;
    default:
        RUN_execvp(arguments, bg);
        break;
    }
}

// turtle happy