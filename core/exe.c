#include "global.h"

void runexecvp(char **argu, int bg) {
    if (bg == 1) // background process
    {
        int pid = fork();
        if (pid == 0) {
            setpgid(0, 0);
            close(STDERR_FILENO); // child
            if (execvp(argu[0], argu) == -1) {
                perror("INVALID COMMAND");
                exit(0);
            }
        } else if (pid > 0) {
            previousid = pid; // stores the process id of most recent process

            if (jobslen < 0) // add the process in job array
                jobslen = 0;
            jobs[jobslen].id = pid;
            strcpy(jobs[jobslen].name, argu[0]);
            jobs[jobslen].status = 1;

            jobslen++;
        }
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            // setpgid(0,0);
            if (execvp(argu[0], argu) == -1)
                perror("INVALID COMMAND");
            exit(0);
        } else if (pid > 0) {

            previousid = pid;
            int shellpid = getpid(); // forground process
            if (jobslen < 0)         // add the process in job array
                jobslen = 0;
            jobs[jobslen].id = pid;
            strcpy(jobs[jobslen].name, argu[0]);
            jobs[jobslen].status = 0;
            jobslen++;
            int status;
            waitpid(pid, &status, WUNTRACED);

            if (WIFSTOPPED(status)) {
                jobs[jobslen - 1].status = 1;
            }
        }
    }
}
