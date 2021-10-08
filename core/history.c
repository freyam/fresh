#include "global.h"

void addhistory(char *argu) {
    char path[100];
    strcpy(path, tilda);
    strcat(path, "/history.log");
    int fd1 = open(path, O_WRONLY | O_CREAT, 0777);
    if (fd1 < 0) {
        perror("Unable to History File!!\n");
        exit(0);
    }
    lseek(fd1, 0, SEEK_END);
    write(fd1, argu, strlen(argu));
    write(fd1, "!", 1);
    close(fd1);
    int fd3 = open(path, O_RDWR);
    if (fd3 < 0) {
        perror("Unable to History File!!\n");
        exit(0);
    }
    int sz = read(fd3, buffer, 100000);
    int j = 0, c = 0;
    for (int i = sz - 1; i >= 0; i--) {
        if (buffer[i] == '!') {
            c++;
            if (c > 20) {
                j = i + 1;
                break;
            }
        }
    }
    truncate(path, 0);
    close(fd3);
    int fd2 = open(path, O_RDWR);
    if (fd2 < 0) {
        perror("Unable to Open History File!!\n");
        exit(0);
    }
    write(fd2, buffer + j, sz - j);
    close(fd2);
}

void printhistory(int num) {
    char path[100];
    strcpy(path, tilda);
    strcat(path, "/history.log");
    int fd1 = open(path, O_RDWR);
    if (fd1 < 0) {
        perror("Unable to Open File!!\n");
        exit(0);
    }
    int sz = read(fd1, buffer, 100000);
    int j = 0, c = 0;

    for (int i = sz - 1; i >= 0; i--) {
        if (buffer[i] == '!') {
            c++;
            if (c > num) {
                j = i + 1;
                break;
            }
        }
    }
    for (int i = j; i < sz; i++) {
        if (buffer[i] == '!')
            printf("\n");
        else
            printf("%c", buffer[i]);
    }

    close(fd1);
    return;
}