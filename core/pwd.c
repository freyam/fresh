#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

void RUN_pwd() {
    char s[1000];
    printf("%s\n", getcwd(s, 1000));
}

// turtle happy