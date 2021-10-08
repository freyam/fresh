#include "global.h"
int redirect(char *s, int fd, int append) {
    int copy = dup(fd); // makes copy of fd
    int fd1;
    if (fd == 0) {
        fd1 = open(s, O_RDONLY);
        if (fd1 < 0) {
            perror("Error in opening input file");

            return -1;
        }

    } else {
        if (append == 0)
            fd1 = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            fd1 = open(s, O_WRONLY | O_CREAT, 0644);
        if (fd1 < 0) {
            perror("Error in opening output file");
            return -1;
        }
    }
    if (append == 1) {
        lseek(fd1, 0, SEEK_END); // for appending, set the file pointer to the end of the file
                                 // lseek(fd,0,SEEK_END);
    }
    dup2(fd1, fd); // for redirecting

    return copy;
}
