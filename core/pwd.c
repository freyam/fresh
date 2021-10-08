#include "global.h"

void runpwd() {
    char s[100];
    printf("%s\n", getcwd(s, 100));
}
