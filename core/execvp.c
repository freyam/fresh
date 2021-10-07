#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

// void add_process(char name[], int pid) {
//     proc *node = malloc(sizeof(proc));
//     strcpy(node->name, name);
//     node->pid = pid;
//     node->next = NULL;
//     if (head == NULL) {
//         head = node;
//     } else {
//         node->next = head;
//         head = node;
//     }
// }

// void search(int pid) {
//     proc *node = head;
//     while (node != head) {
//         if (node->pid == pid) {
//             printf("\n%s", node->name);
//             return;
//         }
//     }
//     printf("\nNon-Existant");
// }

void RUN_execvp(char **argu, int bg) {
    if (bg) {
        int pid = fork();
        if (pid == 0) {
            setpgid(0, 0);
            close(STDERR_FILENO);
            if (execvp(argu[0], argu) == -1)
                perror("INVALID COMMAND");
            return;
        } else {
            printf("%d\n", pid);
        }
    } else {
        int pid = fork();
        if (pid == 0) {
            if (execvp(argu[0], argu) == -1)
                perror("INVALID COMMAND");
            return;
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, WUNTRACED);
        }
    }
}

// turtle happy