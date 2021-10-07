#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

typedef struct history {
    char command[512];
    struct history *next;
} hist;

hist *his_start;

void next_ele(char str[], hist *node) {
    if (node == NULL) {
        node = his_start;
    } else if (node->next != NULL) {
        node = node->next;
    }
    strcpy(str, node->command);
    printf("%s", node->command);
}

void load_history() {
    char path[100];
    strcpy(path, tilda);
    strcat(path, "/history.log");
    hist *node = malloc(sizeof(hist));
    his_start = node;
    node->command[0] = '\0';
    node->next = NULL;
    int fd1 = open(path, O_RDWR);
    if (fd1 < 0) {
        perror("Unable to Open File!!\n");
        exit(0);
    }
    int sz = read(fd1, buffer, 100000);
    int j = 0, c = 0;

    for (int i = sz - 1; i >= 0; i--) {
        if (buffer[i] == '!') {
            c++;
            if (c > 20) {
                j = i + 1;
                break;
            }
        }
    }
    for (int i = j; i < sz; i++) {
        if (buffer[i] == '!') {
            hist *new_node = malloc(sizeof(hist));
            new_node->command[0] = '\0';
            new_node->next = NULL;
            node->next = new_node;
            node = new_node;
            // printf("\n");
        } else {
            // strcat(node->command, buffer[i]);
            node->command[strlen(node->command) + 1] = buffer[i];
            node->command[strlen(node->command) + 2] = '\0';
            // printf("%c", buffer[i]);
        }
    }

    close(fd1);
    return;
}

void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
 */
char *input() {
    char *inp = (char *)malloc(sizeof(char) * 100);
    char c;
    load_history();
    hist *node = NULL;
    setbuf(stdout, NULL);
    enableRawMode();
    memset(inp, '\0', 100);
    int pt = 0;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (iscntrl(c)) {
            if (c == 10) {
                printf("\n");
                break;
            } else if (c == 27) {
                char buf[3];
                buf[2] = 0;
                if (read(STDIN_FILENO, buf, 2) == 2) { // length of escape code
                    if (buf[0] == 91 && buf[1] == 65) {
                        while (pt > 0) {
                            if (inp[pt - 1] == 9) {
                                for (int i = 0; i < 7; i++) {
                                    printf("\b");
                                }
                            }
                            inp[--pt] = '\0';
                            printf("\b \b");
                        }
                        next_ele(inp, node);
                    }
                }
            } else if (c == 127) { // backspace
                if (pt > 0) {
                    if (inp[pt - 1] == 9) {
                        for (int i = 0; i < 7; i++) {
                            printf("\b");
                        }
                    }
                    inp[--pt] = '\0';
                    printf("\b \b");
                }
            } else if (c == 9) { // TAB character
                inp[pt++] = c;
                for (int i = 0; i < 8; i++) { // TABS should be 8 spaces
                    printf(" ");
                }
            } else if (c == 4) {
                exit(0);
            } else {
                printf("%d\n", c);
            }
        } else {
            inp[pt++] = c;
            printf("%c", c);
        }
    }
    disableRawMode();
    return strdup(inp);
}

// turtle sad