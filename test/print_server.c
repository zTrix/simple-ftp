/**
 * print server by zTrix, create server socket and print all of what it heard
 * for ftp debug
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "utils.h"

#define BUF_SIZE 1024
int server = -1;
int client = -1;

void ouch(int i) {
    int st;
    if (server >= 0) {
        st = close(server);
        printf("server closed ... %d\n", st);
    }
    if (client >= 0) {
        st = close(client);
        printf("client closed ... %d\n", st);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: ./print_server <port>\n");
        exit(0);
    }
    signal(SIGINT, ouch);
    signal(SIGTERM, ouch);
    int port = atoi(argv[1]);
    struct sockaddr_in client_addr;
    uint32_t len = sizeof(client_addr);
    server = new_server(INADDR_ANY, port, 1);
    char buf[1024];
    int n;
    client = accept(server, (struct sockaddr *)&client_addr, &len);
    printf("[ II ] client accpeted, addr is %s: %hu \n", inet_ntoa(*(struct in_addr *)&client_addr.sin_addr.s_addr), ntohs(client_addr.sin_port));
    while ((n = recv(client, buf, BUF_SIZE, 0)) > 0) {
        buf[n] = 0;
        printf("%s",buf);
    }
    printf("[ II ] connection closed\n");
    return 0;
}
