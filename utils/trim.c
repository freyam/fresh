#include "global.h"

char *trim2(char *d, const char *s) {
    if (s == NULL || d == NULL)
        return NULL;

    const unsigned char *p = (const unsigned char *)s;
    while (isspace(*p))
        p++;

    unsigned char *dst = (unsigned char *)d;
    unsigned char *end = dst;
    while (*p != '\0') {
        if (!isspace(*dst++ = *p++))
            end = dst;
    }

    *end = '\0';
    return d;
}

char *trim(char *s) { // trims the string
    return trim2(s, s);
}
char *slice(char *src, int l, int f) {
    char *ret = (char *)calloc(sizeof(char), f - l + 2); // slices the string
    for (int i = l; i <= f; i++)
        ret[i - l] = src[i];
    ret[f - l + 1] = '\0';
    return ret;
}
