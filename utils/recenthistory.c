#include "global.h"

void giverecenthistory(int up, char *argu) {
    char path[100];
    strcpy(path, tilda);
    strcat(path, "/history.log");
    int fd1 = open(path, O_RDWR);
    if (fd1 < 0) {
        perror("Unable to Open File!!\n");
        exit(0); //gives the previous command typed
    }
    int sz = read(fd1, buffer, 100000);
    int j = 0, c = 0;

    for (int i = sz - 1; i >= 0; i--) {
        if (buffer[i] == '!') {
            c++;
            if (c == (up + 1)) {
                j = i + 1;
                break;
            }
        }
    }
    int c1 = 0;
    for (int i = j; i < sz; i++) {
        if (buffer[i] == '!')
            break;
        else
            argu[c1++] = buffer[i];
    }
    argu[c1++] = '\0';
    close(fd1);
}
