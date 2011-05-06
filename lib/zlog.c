#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define FTP_SESSION "SESSION"
#define FTP_DAEMON  "DAEMON "

void err(int type, const char *fmt, ...) {
    printf("\033[22;31m [ EE ] [ %s %d ]: ", type ? FTP_SESSION : FTP_DAEMON, getpid());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\e[0m\n");
}

void warn(int type, const char *fmt, ...) {
    printf("\033[22;33m [ WW ] [ %s %d ]: ", type ? FTP_SESSION : FTP_DAEMON, getpid());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\e[0m\n");
}

void info(int type, const char *fmt, ...) {
    printf("\033[22;32m [ II ] [ %s %d ]: ", type ? FTP_SESSION : FTP_DAEMON, getpid());
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\e[0m\n");
}

