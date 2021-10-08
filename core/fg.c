#include "global.h"

void fg_or_bg(char **argu, int bg) {
    if (argu[1] == NULL) {
        return;
    }
    int pid;
    sscanf(argu[1], "%d", &pid);

    int c = 0;
    int flag = 0;
    int ppid;
    int j;
    for (int i = 0; i < jobslen; i++) {
        if (jobs[i].status == 1)
            c++;
        if (c == pid) {
            ppid = jobs[i].id;
            flag = 1;
            j = i;
            break;
        }
    }
    if (flag == 0) {
        perror("invalid id!!\n");
        return;
    }
    previousid = ppid;
    if (bg == 0) {
        int status;
        pid_t shellpid = getpid();
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        tcsetpgrp(0, getpgid(ppid));
        kill(ppid, SIGCONT);
        waitpid(ppid, &status, WUNTRACED);
        tcsetpgrp(0, shellpid);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);

        jobs[j].status = 0;
        if (WIFSTOPPED(status)) {
            jobs[j].status = 1;
        }
        return;
    } else {
        kill(ppid, SIGCONT);
        jobs[j].status = 1;
    }
    return;
}
