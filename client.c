#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include "client.h"
#include "serverinfo.h"
#include "userinfo.h"
#include "util.h"

int recv_and_process_message(int sock) {
    char *buf;
    char *tm_no_newline;
    time_t t;
    ssize_t size;

    buf = tm_no_newline = NULL;
    buf = malloc_wrapper(
        MAX_MSG_SIZE + 1); /* Standard specifies maximum message size as 512 */
    size = recv(sock, buf, MAX_MSG_SIZE, 0);
    
    if(size == -1) { /* recv failure */
        return (EXIT_FAILURE);
    }

    buf[size] = '\0';
#ifdef DEBUG
    printf("%s", buf);
#endif
    if (strstr(buf, "PING")) {
#ifdef DEBUG
        fprintf(stderr,
                "Sending PONG message in response to PING from server\n");
#endif
        send_all(sock, "PONG *\r\n");
    }
    if (strstr(buf, " PRIVMSG ")) {
        t = time(NULL);
        tm_no_newline = strtok(ctime(&t), "\n");
        printf("(%s) %s", tm_no_newline, buf); /* log message command with timestamp */
    }
    free(buf);

    return (EXIT_SUCCESS);
}

void send_login(int sock, struct user *info) {
    sendall_fmt(sock, "NICK %s\r\nUSER %s * * :%s\r\n", info->nick1,
                info->username, info->realname);
}

void join_channel(int sock, struct server *serv) {
    sendall_fmt(sock, "JOIN %s\r\n", serv->channel);
}
