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
pid_t forkpid = 1;
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
    if (forkpid > 0) {      // ftpd
        if (server >= 0) {
            int st = close(server);
            info("[ DAEMON ]: pid %d, shutdown ftp ... %d", getpid(), st);
        }
    } else {                // session
        if (client >= 0) {
            int st = close(client);
            info("[ SESSION %d ]: shutdown ftp session... %d", getpid(), st);
        }
    }
    exit(0);
}

enum FTP_CMD parse_cmd(char *buf, int len) {
    int i,j;
    for (i=0; i<FTP_CMD_COUNT; i++) {
        for (j=0; FTP_CMD_LIST[i].name[j] != '\0' && j < len; j++) {
            if (FTP_CMD_LIST[i].name[j] != buf[j]) break;
        }
        if (FTP_CMD_LIST[i].name[j] == '\0')
            return FTP_CMD_LIST[i].cmd;
    }
    return INVALID;
}

/**
 * handle a newly accepted ftp session
 *
 */
void handle_session(int client) {
    struct sockaddr_in addr;
    uint32_t addrlen = sizeof(addr);
    //getsockname(client, (struct sockaddr*)&addr, &addrlen);
    //info("Server Address: %s", inet_ntoa(addr.sin_addr));
    send_str(client, FTP_RDY);
    int i, n;
    while ((n=recv(client, buf, BUF_SIZE, MSG_PEEK)) > 0) {
        if (!running) break;
        buf[n] = '\0';
        info("[ SESSION %d ]: recved %d bytes: %s", getpid(), n, buf);
        for (i=0; i<n; i++) {
            if (buf[i] == '\n') break;
        }
        if (buf[i] != '\n') {
            err("[ SESSION %d ]: no line break found", getpid());
            break;
        }
        n = recv(client, buf, i+1, 0);
        buf[n] = '\0';
        enum FTP_CMD cmd = parse_cmd(buf, n);
        info("[ SESSION %d ]: cmd: %s, %d", getpid(), FTP_CMD_LIST[cmd].name, cmd);
        switch(cmd) {
            case NOOP:
                send_str(client, FTP_OK);
            break;
        }
    }
    info("[ SESSION %d ]: exit session", getpid());
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
        err("[ DAEMON ] can not create server, return code is %d, socket already in use", server);
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

        forkpid = fork();
        if (forkpid == -1) {
            err("fork server error");
        } else if (forkpid == 0) {      // child
            server = -1;        // avoid killing server on Ctrl-C
            info("new ftp session");
            handle_session(client);
            exit(0);
        } else if (forkpid > 0) {       // myself
            client = -1;
        }
    }
    
    info("exit ftpd");
    return 0;
}

