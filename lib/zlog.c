#include <stdio.h>
#include <stdarg.h>

void err(char *fmt, ...) {
    printf(" [ EE ] ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

void warn(char *fmt, ...) {
    printf(" [ WW ] ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

void info(char *fmt, ...) {
    printf(" [ II ] ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

