#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

void print_dir() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    int n = strlen(tilda);
    int flag = 1;
    if (strlen(cwd) < n) {
        flag = 0;

    } else {
        for (int i = 0; i < n; i++) {
            if (cwd[i] != tilda[i]) {
                flag = 0;
                break;
            }
        }
    }
    if (flag) {
        printf("~%s", cwd + n);

    } else {
        printf("%s", cwd);
    }
}

char *get_dir(char *cwd) {
    int n = strlen(tilda);
    int flag = 1;
    if (strlen(cwd) < n) {
        flag = 0;

    } else {
        for (int i = 0; i < n; i++) {
            if (cwd[i] != tilda[i]) {
                flag = 0;
                break;
            }
        }
    }
    if (flag) {
        char *temp = (char *)calloc((strlen(cwd) + 1), sizeof(char));
        strcpy(temp, "~");
        strcat(temp, cwd + n);
        return temp;
    } else {
        char *temp = (char *)calloc((strlen(cwd) + 1), sizeof(char));
        strcat(temp, cwd);
        return temp;
    }
}

// turtle happy