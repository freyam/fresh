#include <arpa/inet.h>
#include <curses.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pwd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

void show_prompt();

void print_dir();
char *get_dir(char *);

void callpinfo(int);
void history_append(char *);
void show_history(int);

void RUN_cd(char *, int, int);
void RUN_echo(char *);
void RUN_pwd();
void RUN_ls(char *arr1, char *arr2, int arg1, int arg2);
void RUN_execvp(char **, int);

void command_executor(char *);
void command_separator(char *);

int takeInput(char *);
char *input();

typedef struct bg {
    char name[512];
    int pid;
    struct bg *next;
} proc;

extern proc *head;

void search(int pid);