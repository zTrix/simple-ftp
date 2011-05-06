#ifndef __FTP_MYSOCKET_H__
#define __FTP_MYSOCKET_H__

#include <stdio.h>
#include "sys/socket.h"

struct sockaddr new_addr(uint32_t inaddr, unsigned short port);
int new_server(uint32_t inaddr, uint16_t port, int backlog);
int new_client(uint32_t srv_addr, unsigned short port);
int send_str(int peer, const char *fmt, ...);
int send_file(int peer, FILE *f);
int send_path(int peer, char *file, uint32_t offset);
int recv_file(int peer, FILE *f);
int recv_path(int peer, char *file, uint32_t offset);

int parse_number(const char *buf, uint32_t *number);
int parse_addr_port(const char *buf, uint32_t *addr, uint16_t *port);
char * parse_path(const char *buf);
char * n2a(uint32_t addr);
#endif

