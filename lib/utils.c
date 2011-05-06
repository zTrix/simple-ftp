#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "vars.h"
#include "utils.h"

struct sockaddr new_addr(uint32_t inaddr, unsigned short port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(inaddr);
    addr.sin_port = htons(port);
    return *(struct sockaddr *)&addr;
}

int new_server(uint32_t inaddr, uint16_t port, int backlog) {
    int ret = 0;
    int server;
    server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr addr = new_addr(inaddr, port);
    if (bind(server, &addr, sizeof(addr)) < 0) {
        return -2;
    }
    if (listen(server, backlog) < 0) {
        return -3;
    }
    return server;
}

/**
 * new client 
 * @return {int} status, -2 create socket error, -1 connect error
 */
int new_client(uint32_t srv_addr, unsigned short port) {
    int client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) return -2;
    struct sockaddr server = new_addr(srv_addr, port);
    int st = connect(client, &server, sizeof(server));
    if (st < 0) return -1;
    return client;
}

int send_str(int peer, const char* fmt, ...) {
    va_list args;
    char msgbuf[BUF_SIZE];
    va_start(args, fmt);
    vsnprintf(msgbuf, sizeof(msgbuf), fmt, args);
    va_end(args);
    return send(peer, msgbuf, strlen(msgbuf), 0);
}

/**
 * -1 error, 0 ok
 */
int send_file(int peer, FILE *f) {
    char filebuf[BUF_SIZE+1];
    int n, ret = 0;
    while ((n=fread(filebuf, 1, BUF_SIZE, f)) > 0) {
        int st = send(peer, filebuf, n, 0);
        if (st < 0) {
            err(1, "send file error, errno = %d, %s", errno, strerror(errno));
            ret = -1;
            break;
        } else {
            filebuf[n] = 0;
            info(1, " %d bytes sent", st);
        }
    }
    return ret;
}

/**
 *  -1 error opening file, -2 send file error, -3 close file error
 */
int send_path(int peer, char *file, uint32_t offset) {
    FILE *f = fopen(file, "rb");
    if (f) {
        fseek(f, offset, SEEK_SET);
        int st = send_file(peer, f);
        if (st < 0) {
            return -2;
        }
    } else {
        return -1;
    }
    int ret = fclose(f);
    return ret == 0 ? 0 : -3;
}

int recv_file(int peer, FILE *f) {
    char filebuf[BUF_SIZE];
    int n;
    while ((n=recv(peer, filebuf, BUF_SIZE, 0)) > 0) {
        fwrite(filebuf, 1, n, f);
    }
    return n;
}

/**
 * recv file by file path
 * @param {int} peer, peer socket
 * @param {char *} file path
 * @param {int} offset
 * @return {int} status, 
 *              -1 means recv_file error, 
 *              -2 means file open failure, 
 *              EOF means close file error
 * 
 */
int recv_path(int peer, char *file, uint32_t offset) {
    FILE *f = fopen(file, "wb");
    if (!f) return -2;
    fseek(f, offset, SEEK_SET);
    int st = recv_file(peer, f);
    int cl = fclose(f);
    return st < 0 ? st : cl;
}

int parse_number(const char *buf, uint32_t *number) {
    int f = -1, i;
    char tmp[BUF_SIZE] = {0};
    int ret = -1;
    for (i=0; buf[i]!=0 && i<BUF_SIZE; i++) {
        if (!isdigit(buf[i])) {
            if (f >= 0) {
                memcpy(tmp, &buf[f], i-f);
                tmp[i-f] = 0;
                *number = atoi(tmp);
                ret = 0;
                f = -1;
                break;
            }
        } else {
            if (f < 0) {
                f = i;
            }
        }
    }
    return ret;
}

int parse_addr_port(const char *buf, uint32_t *addr, uint16_t *port) {
    int i;
    *addr = *port = 0;
    int f = -1;
    char tmp[BUF_SIZE] = {0};
    int cnt = 0;
    int portcnt = 0;
    for(i=0; buf[i]!=0 && i<BUF_SIZE; i++) {
        if(!isdigit(buf[i])) {
            if (f >= 0) {
                memcpy(tmp, &buf[f], i-f);
                tmp[i-f] = 0;
                if (cnt < 4) {
                    *addr = (*addr << 8) + (0xff & atoi(tmp));
                    cnt++;
                } else if (portcnt < 2) {
                    *port = (*port << 8) + (0xff & atoi(tmp));
                    portcnt++;
                } else {
                    break;
                }
                f = -1;
            }
        } else {
            if (f < 0) {
                f = i;
            }
        }
    }
    return cnt == 4 && portcnt == 2;
}

char * parse_path(const char *buf) {
    char * path = (char *)malloc(BUF_SIZE);
    int i, j;
    for (i=0; buf[i]!=' ' && i < BUF_SIZE; i++);
    if (i == BUF_SIZE) return NULL;
    i++;
    for (j=i; buf[j]!='\r' && buf[j]!= '\n' && j < BUF_SIZE; j++);
    memcpy(path, &buf[i], j-i);
    path[j-i] = 0;
    return path;
}

char * n2a(uint32_t addr) {
    uint32_t t = htonl(addr);
    return inet_ntoa(*(struct in_addr *)&t);
}

