#include <arpa/inet.h>
#include <ctype.h>
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];
extern char *buf;

extern int jobslen;

typedef struct job {
    int id;
    char name[1000];
    int status;
} job;

extern int cron1;
extern int replaypid;
extern int previousid;
extern job jobs[10000];

char *slice(char *, int l, int f);
char *trim(char *);
char *trim2(char *, const char *);
int redirect(char *, int, int);
int takeInput(char *);
void addhistory(char *);
void show_prompt();
void callpinfo(int);
char *get_dir(char *);
void commandsep(char *);
void execute_pipe(char *);
void execute(char *);
void killall();
void fg_or_bg(char **, int);
void giverecenthistory(int, char *);
void print_dir();
void printhistory(int);
void printjobs();
void replay(char **, int);
void runcd(char *, int, int);
void runecho(char *);
void runexecvp(char **, int);
void runls(char *, char *, int, int);
void runpwd();
void sig(char **);
void sigintHandler(int);
void sigtstpHandler(int);
