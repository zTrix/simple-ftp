#include <stdio.h>
#include <stdarg.h>

void err(char *fmt, ...) {
    printf("\033[22;31m [ EE ] ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\e[0m\n");
}

void warn(char *fmt, ...) {
    printf("\033[22;33m [ WW ] ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\e[0m\n");
}

void info(char *fmt, ...) {
    printf("\033[22;32m [ II ] ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\e[0m\n");
}

