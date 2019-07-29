#ifndef SERVERINFO_H
#define SERVERINFO_H
struct server {
	char *ip;
	short unsigned int port;
	char *channel;
}server;

struct server *init_server(struct server *serv);
void cleanup_server(struct server *serv);
#endif /* SERVERINFO_H */
