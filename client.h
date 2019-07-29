#ifndef CLIENT_H
#define CLIENT_H
#include "userinfo.h"
#include "serverinfo.h"

#define MAX_MSG_SIZE 512

int recv_and_process_message(int sock);
void send_login(int sock, struct user *info);
void join_channel(int sock, struct server *serv);
#endif /* CLIENT_H */
