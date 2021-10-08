#include "global.h"

void callpinfo(int pid) {
    char pp[100];
    if (pid == -1) {
        pid = getpid();
    }
    sprintf(pp, "%d", pid);
    char path1[100] = "/proc/";
    char path2[100];
    strcat(path1, pp);
    strcpy(path2, path1);
    strcat(path1, "/stat");
    strcat(path2, "/exe");

    char buffer[10000], buffer2[10000], buffer3[10000];
    int fd = open(path1, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Unable to Open File!\n");
        return;
    }

    read(fd, buffer, 10000);
    char *ptr = strtok(buffer, " ");
    char *tokens[10000];
    int count_tokens = 0;
    while (ptr != NULL) {
        tokens[count_tokens++] = ptr;
        ptr = strtok(NULL, " ");
    }

    int length = readlink(path2, buffer2, 5000);
    buffer2[length] = '\0';

    char plus = (!strcmp(tokens[0], tokens[7])) ? '+' : '\0';

    printf("pid -- %s\n", tokens[0]);
    printf("Process Status -- %s%c\n", tokens[2], plus);
    printf("Memory -- %s\n", tokens[22]);
    printf("Executable Path -- %s\n", get_dir(buffer2));
}