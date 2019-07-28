#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "connect.h"
#include "serverinfo.h"
#include "util.h"

int connect_to_server(struct server *serv) {
    int sock;
    struct sockaddr_in sa;

    memset(sa.sin_zero, '\0', sizeof(sa.sin_zero));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(serv->port);
    sa.sin_addr.s_addr = inet_addr(serv->ip);

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) {
#ifdef DEBUG
        fprintf(stderr, "Failed to create socket\n");
#endif
        return (EXIT_FAILURE);
    }
#ifdef DEBUG
    else {
        fprintf(stderr, "Successfully created socket\n");
    }
#endif

    if ((connect(sock, (struct sockaddr *)&sa, sizeof(sa))) == -1) {
#ifdef DEBUG
        fprintf(stderr, "Failed to connect to server %s on port %hu\n",
                serv->ip, serv->port);
#endif
        return (EXIT_FAILURE);
    }
#ifdef DEBUG
    else {
        fprintf(stderr, "Successfully connected to server %s on port %hu\n",
                serv->ip, serv->port);
    }
#endif

    return sock;
}
