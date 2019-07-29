#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "client.h"
#include "connect.h"
#include "serverinfo.h"
#include "userinfo.h"
#include "util.h"

void cleanup_all(struct user *userinfo, struct server *serverinfo, int sock);

void cleanup_all(struct user *userinfo, struct server *serverinfo, int sock) {
    cleanup_user(userinfo);
    cleanup_server(serverinfo);
    close(sock);
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct user *userinfo;
    struct server *servinfo;

    /* todo: read from configuration file */
    if (argc < 2) {
        die("Insufficient arguments: this program takes one argument, bot nickname");
    }

    /* initializes user info struct */
    userinfo = NULL;
    userinfo = init_user(userinfo);

    userinfo->nick1 = argv[1];
    userinfo->nick2 = "irctest"; /* TODO: implement nick switching for already used nicknames */
    userinfo->nick3 = "irctest";
    userinfo->username = "irctest";
    userinfo->realname = "real_name";
    check_user(userinfo); /* make sure usernames are defined and within the standard */

    /* initializes server info struct */
    servinfo = NULL;
    servinfo = init_server(servinfo);

    servinfo->ip = "127.0.0.1";
    servinfo->port = 6667;
    servinfo->channel = "#test";

    /* connect to server, returns socket fd number */
    sockfd = connect_to_server(servinfo);
    if (sockfd == EXIT_FAILURE) {
        cleanup_all(userinfo, servinfo, sockfd);
        die("Failed to connect to server");
    }

    send_login(sockfd, userinfo);
    join_channel(sockfd, servinfo);

    while (recv_and_process_message(sockfd) == EXIT_SUCCESS) { /* main recv loop */
        ;
    }

    cleanup_all(userinfo, servinfo, sockfd);
    return (EXIT_SUCCESS);
}
