#include "global.h"

void sig(char **argu) {

    if (argu[1] == NULL) {
        return;
    }
    if (argu[2] == NULL) {
        return;
    }
    int ppid;

    int pid;
    sscanf(argu[1], "%d", &pid);
    int c = 0;
    int flag = 0;
    for (int i = 0; i < jobslen; i++) {

        if (jobs[i].status == 1)
            c++; // finds the actual process id of the process

        if (c == pid) {
            ppid = jobs[i].id;
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        perror("invalid id\n");
        return;
    }
    int sig;
    sscanf(argu[2], "%d", &sig);
    kill(ppid, sig); // sends signal using kill syscall
    return;
}

void killall() {
    for (int i = 0; i < jobslen; i++) {
        if (jobs[i].status == 1) {
            kill(jobs[i].id, 9); // sends signal 9 to every process
            jobs[i].status = 0;
        }
    }
    return;
}