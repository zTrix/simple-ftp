#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "vars.h"
#include "zlog.h"
#include "mysocket.h"

int server = -1, client = -1, running = 0;
pid_t pid = 1;
char buf[BUF_SIZE];

/**
 * handle Ctrl-C 
 * 
 * @param {int} socket fd
 *
 * the parent and all its children will recieve kill signal and execute this
 */
void ouch(int n) {
    running = 0;
    puts("");
    if (server >= 0) {
        int st = close(server);
        info("pid: %d, shutdown server ... %d", pid, st);
    }
    if (client >= 0) {
        int st = close(client);
        info("pid: %d, shutdown client ... %d", pid, st);
    }
    exit(0);
}

/**
 * handle a newly accepted ftp session
 *
 */
void handle_session(int client) {
    struct sockaddr_in addr;
    uint32_t addrlen = sizeof(addr);
    getsockname(client, (struct sockaddr*)&addr, &addrlen);
    info("Server Address: %s", inet_ntoa(addr.sin_addr));
    while (running) {
        
    }
    info("exit handle_session");
}

int main(int argc, char *argv[]){
    int port = LISTEN_PORT;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    signal(SIGCHLD, SIG_IGN);   // ignore child termination signal
    signal(SIGINT, ouch);       // catch Ctrl-C 
    signal(SIGTERM, ouch);

    server = new_server(LISTEN_ADDR, port, MAX_CONNECTIONS);
    if (server < 0) {
        err("can not create server, return code is %d", server);
        exit(1);
    }

    running = 1;

    struct sockaddr_in client_addr;
    while (running) {
        uint32_t l = sizeof(client_addr);
        client = accept(server, (struct sockaddr *)&client_addr, &l);

        if (!running) break;
        if (client < 0) {
            err("accept client error: %d", client);
            exit(2);
        }
        info("client connected: %s", inet_ntoa(client_addr.sin_addr));

        pid = fork();
        if (pid == -1) {
            err("fork server error");
        } else if (pid == 0) {      // child
            server = -1;        // avoid killing server on Ctrl-C
            info("new ftp session");
            handle_session(client);
            exit(0);
        } else if (pid > 0) {       // myself
            client = -1;
        }
    }
    
    info("exit ftpd");
    return 0;
}

