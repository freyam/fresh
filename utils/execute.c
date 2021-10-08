#include "global.h"

void db1() {
    perror("heloo");
    exit(0);
}

void execute(char *strinput) {

    int n = strlen(strinput);
    int *arr = (int *)calloc(sizeof(int), n + 1);
    int restore[3] = {0, 0, 0};
    for (int i = 0; i < n - 1; i++) {
        if (strinput[i] == '>' || strinput[i] == '<') {
            arr[i] = 1;
        }
    }
    for (int i = 0; i < n - 2; i++) {
        if (arr[i] == 1 && arr[i + 1] == 1 && arr[i + 2] == 1) {
            perror("invalid syntax!!\n");
            return;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (strinput[i] == '>' && strinput[i + 1] == '<') {
            perror("invalid syntax!!\n");
            return;
        }
        if (strinput[i] == '<' && strinput[i + 1] == '>') {
            perror("invalid syntax!!\n");
            return;
        }
    }

    restore[0] = 0;
    restore[1] = 1;
    int p1 = 0;
    char str[100] = {0};
    while (p1 != n && strinput[p1] != '>' && strinput[p1] != '<') {
        str[p1] = strinput[p1];
        p1++;
    }

    for (int i = 0; i < n; i++) {
        if (strinput[i] == '>' || strinput[i] == '<') {
            if (strinput[i] == '>' && (i + 1) < n && strinput[i + 1] == '>') {
                int l = i + 2;
                if (l == n) {
                    perror("invalid syntax!!");
                    return;
                }
                int f = n - 1;
                for (int j = l; j < n; j++) {
                    if (strinput[j] == '>' || strinput[j] == '<') {

                        f = j - 1;
                        break;
                    }
                }

                char *s = trim(slice(strinput, l, f));
                if (!strcmp(s, ""))
                    db1();

                dup2(restore[1], 1);

                if ((restore[1] = redirect(s, 1, 1)) == -1) {
                    return;
                }
                i++;
                continue;
            }
            int l = i + 1;

            int f = n - 1;
            for (int j = i + 1; j < n; j++) {
                if (strinput[j] == '>' || strinput[j] == '<') {
                    f = j - 1;
                    break;
                }
            }

            char *s = trim(slice(strinput, l, f));
            if (!strcmp(s, "")) {
                perror("invalid syntax!!\n");
                return;
            }

            int fd = 0;
            if (strinput[i] == '<') {
                dup2(restore[0], 0);
                fd = 0;
            } else {
                dup2(restore[1], 1);
                fd = 1;
            }

            if ((restore[fd] = redirect(s, fd, 0)) == -1)
                return;
        }
    }

    char mycommands[16][100];
    strcpy(mycommands[0], "cd");
    strcpy(mycommands[1], "pwd");
    strcpy(mycommands[2], "ls");
    strcpy(mycommands[3], "quit");
    strcpy(mycommands[4], "echo");
    strcpy(mycommands[5], "history");
    strcpy(mycommands[6], "pinfo");
    strcpy(mycommands[8], "jobs");
    strcpy(mycommands[9], "sig");
    strcpy(mycommands[10], "fg");
    strcpy(mycommands[11], "bg");
    strcpy(mycommands[12], "killall");
    strcpy(mycommands[15], "replay");
    char *arguments[100] = {'\0'};
    char *ptr = strtok(str, " ");
    int j = -1;
    for (int i = 0; i < 16; i++) {
        if (strcmp(ptr, mycommands[i]) == 0) {
            j = i;
            break;
        }
    }
    int c = 1;
    int len = 0;
    while (ptr != NULL) {

        arguments[len++] = ptr;
        if (arguments[len - 1][0] == '~') {
            char temp[1000];
            strcpy(temp, tilda);
            strcat(temp, arguments[len - 1] + 1);
            arguments[len - 1] = temp;
        }
        ptr = strtok(NULL, " ");
    }

    int bg = 0;
    if (!strcmp(arguments[len - 1], "&")) {

        bg = 1;
        arguments[len - 1] = '\0';
        len--;
    }
    int f1 = 1, f2 = 1, pid = -1;
    int pdd, mode = -1;
    int num = 10;
    if (len == 1) {
        if (j == 0) {
            arguments[1] = tilda;
            len++;
        }
        if (j == 4) {
            arguments[1] = "";
            len++;
        }
        pid = -1;
        f1 = 0;
        f2 = 0;
    } else if (len == 2) {
        if (j == 5) {
            sscanf(arguments[1], "%d", &num);
        }
        sscanf(arguments[1], "%d", &pid);
        f2 = 0;
    } else {
        sscanf(arguments[1], "%d", &pid);
        sscanf(arguments[2], "%d", &pdd);
        if (len > 3) {
            if (strcmp(arguments[3], "interrupt") == 0)
                mode = 0;
            else if (strcmp(arguments[3], "dirty") == 0)
                mode = 1;
        }
    }

    switch (j) {
    case 0:
        runcd(arguments[1], f1, f2);
        break;
    case 1:
        runpwd();
        break;
    case 2:
        runls(arguments[1], arguments[2], f1, f2);
        break;
    case 3:
        killall(), exit(0);
        break;
    case 4:
        runecho(arguments[1]);
        break;
    case 5:
        printhistory(num);
        break;
    case 6:
        callpinfo(pid);
        break;
    case 8:
        printjobs();
        break;
    case 9:
        sig(arguments);
        break;
    case 10:
        fg_or_bg(arguments, 0);
        break;
    case 11:
        fg_or_bg(arguments, 1);
        break;
    case 12:
        killall();
        break;
    case 15:
        replay(arguments, len);
        break;
    default:
        runexecvp(arguments, bg);
        break;
    }

    dup2(restore[0], 0);
    dup2(restore[1], 1);
}
