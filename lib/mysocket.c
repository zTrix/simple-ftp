#include <sys/socket.h>
#include <arpa/inet.h>

int new_server(uint32_t inaddr, uint16_t port, int backlog) {
    int ret = 0;
    int server;
    struct sockaddr_in addr;
    server = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(inaddr);
    addr.sin_port = htons(port);

    if (bind(server, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        return -1;
    }
    if (listen(server, backlog) < 0) {
        return -2;
    }
    return server;
}

