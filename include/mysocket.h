#ifndef __FTP_MYSOCKET_H__
#define __FTP_MYSOCKET_H__

int new_server(uint32_t inaddr, uint16_t port, int backlog);
int close_socket(int socket);

#endif

