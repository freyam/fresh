#include "global.h"

char tilda[100];
char previous[1000];
char buffer[100000];
proc *head = NULL;

void show_prompt() {
    char *user = getenv("USER");
    char hostname[1024];
    hostname[1023] = '\0';

    if (gethostname(hostname, 1023) == -1) {
        perror("hostname");
        exit(1);
    }

    printf("\e[1;32m<%s", user);
    printf("@%s\e[m\e[1;34m:", hostname);
    print_dir();
    printf("\e[m\e[1;32m>\e[m ");
}

void handler(int pid) {
    int pid_status;
    pid_t WPID = waitpid(-1, &pid_status, WNOHANG);
    if (WPID > 0) {
        // search(WPID);
        if (WIFEXITED(pid_status)) {
            fprintf(stderr, "\npid %d exited normally.\n", WPID);
            show_prompt();
            fflush(stdout);
            return;
        }

        else if (WIFSIGNALED(pid_status)) {
            fprintf(stderr, "\n%d pid exited abnormally.\n", WPID);
            show_prompt();
            fflush(stdout);
            return;
        }
    }
}

int main() {
    getcwd(tilda, 100);
    strcpy(previous, "INVALID");

    signal(SIGCHLD, handler);

    while (1) {
        show_prompt();

        char argu[1024];

        if (takeInput(argu) == 0)
            continue;

        command_separator(argu);
    }

    return 0;
}

// turtle happy