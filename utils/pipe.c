#include "global.h"

void execute_pipe(char *strinput) {

    int n = strlen(strinput);
    if (n <= 0)
        return;
    int c = 0;
    for (int i = 0; i < n; i++)
        if (strinput[i] == '|')
            c++;
    if (c == 0) {
        execute(strinput);
        return;
    }
    int j = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (strinput[i] == '|') {
            j = i - 1;
            break;
        }
    }

    int len = 0;
    char *tokens[100];
    char *ptr = strtok(strinput, "|");
    while (ptr != NULL) {
        tokens[len++] = ptr;
        ptr = strtok(NULL, "|");
    }

    int stdin = 0, stdout = 1;

    int arr[2] = {0, 0};
    for (int i = 0; i < len; i++) {
        if (i == 0) // forking for executing every subcommand under pipe  and redirecting
        {           // output and input to pipe
            if (pipe(arr) == -1) {
                perror("pipe failed!!\n");
                exit(0);
            }
            stdout = dup(1);
            dup2(arr[1], 1);

        } else if (i == (len - 1)) {
            close(arr[1]);
            stdin = dup(0);
            dup2(arr[0], 0);
            close(arr[0]);

        } else {
            close(arr[1]);
            stdin = dup(0);
            dup2(arr[0], 0);
            close(arr[0]);
            if (pipe(arr) == -1) {
                perror("pipe failed!!\n");
                exit(0);
            }
            stdout = dup(1);
            dup2(arr[1], 1);
        }

        int pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(0);
        } else if (pid == 0) {
            execute(tokens[i]);
            exit(0);

        } else {
            int status;
            waitpid(pid, &status, 0);
            dup2(stdin, 0);
            dup2(stdout, 1);
        }
    }
}
