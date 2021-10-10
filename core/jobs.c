#include "global.h"

void printjobs(char *raw_input) {
    if (!strcmp(raw_input, "jobs -r")) {
        int c11 = 1;
        for (int i = 0; i < jobslen; i++) {
            if (jobs[i].status == 1) // this condition determines whether the process is in background or not
            {
                char path[100];
                strcpy(path, "/proc/");
                char buf[100];
                sprintf(buf, "%d", jobs[i].id); // finds the status of job
                strcat(path, buf);
                strcat(path, "/status");
                char *tokens[100], *tokenss[100];
                int fd = open(path, O_RDONLY);
                if (fd < 0) {
                    return;
                }
                char buffer[1001];
                read(fd, buffer, 1000);
                char *ptr = strtok(buffer, "\n");
                int c = 0;
                while (ptr != NULL) {
                    tokens[c++] = ptr;
                    ptr = strtok(NULL, "\n");
                }
                int p1 = 0;
                int n = strlen(tokens[2]);
                while (p1 < n && tokens[2][p1] != '(')
                    p1++;
                int p2 = p1 + 1;
                while (p2 < n && tokens[2][p1] != ')') {
                    p2++;
                }
                p1++;
                p2--;
                p2--;
                char *statt = slice(tokens[2], p1, p2);
                if (!strcmp(statt, "sleeping")) {
                    strcpy(statt, "Running");
                    printf("[%d] %s %s [%d]\n", c11, statt, jobs[i].name, jobs[i].id);
                }

                c11++;
            }
        }
        return;
    } else if (!strcmp(raw_input, "jobs -s")) {
        int c11 = 1;
        for (int i = 0; i < jobslen; i++) {
            if (jobs[i].status == 1) // this condition determines whether the process is in background or not
            {
                char path[100];
                strcpy(path, "/proc/");
                char buf[100];
                sprintf(buf, "%d", jobs[i].id); // finds the status of job
                strcat(path, buf);
                strcat(path, "/status");
                char *tokens[100], *tokenss[100];
                int fd = open(path, O_RDONLY);
                if (fd < 0) {
                    return;
                }
                char buffer[1001];
                read(fd, buffer, 1000);
                char *ptr = strtok(buffer, "\n");
                int c = 0;
                while (ptr != NULL) {
                    tokens[c++] = ptr;
                    ptr = strtok(NULL, "\n");
                }
                int p1 = 0;
                int n = strlen(tokens[2]);
                while (p1 < n && tokens[2][p1] != '(')
                    p1++;
                int p2 = p1 + 1;
                while (p2 < n && tokens[2][p1] != ')') {
                    p2++;
                }
                p1++;
                p2--;
                p2--;
                char *statt = slice(tokens[2], p1, p2);
                if (!strcmp(statt, "stopped")) {
                    strcpy(statt, "Stopped");
                    printf("[%d] %s %s [%d]\n", c11, statt, jobs[i].name, jobs[i].id);
                }

                c11++;
            }
        }
        return;
    } else {

        int c11 = 1;
        for (int i = 0; i < jobslen; i++) {
            if (jobs[i].status == 1) // this condition determines whether the process is in background or not
            {
                char path[100];
                strcpy(path, "/proc/");
                char buf[100];
                sprintf(buf, "%d", jobs[i].id); // finds the status of job
                strcat(path, buf);
                strcat(path, "/status");
                char *tokens[100], *tokenss[100];
                int fd = open(path, O_RDONLY);
                if (fd < 0) {
                    return;
                }
                char buffer[1001];
                read(fd, buffer, 1000);
                char *ptr = strtok(buffer, "\n");
                int c = 0;
                while (ptr != NULL) {
                    tokens[c++] = ptr;
                    ptr = strtok(NULL, "\n");
                }
                int p1 = 0;
                int n = strlen(tokens[2]);
                while (p1 < n && tokens[2][p1] != '(')
                    p1++;
                int p2 = p1 + 1;
                while (p2 < n && tokens[2][p1] != ')') {
                    p2++;
                }
                p1++;
                p2--;
                p2--;
                char *statt = slice(tokens[2], p1, p2);
                if (!strcmp(statt, "sleeping")) {
                    strcpy(statt, "Running");
                    printf("[%d] %s %s [%d]\n", c11, statt, jobs[i].name, jobs[i].id);
                } else if (!strcmp(statt, "stopped")) {
                    strcpy(statt, "Stopped");
                    printf("[%d] %s %s [%d]\n", c11, statt, jobs[i].name, jobs[i].id);
                }

                c11++;
            }
        }
        return;
    }
}
