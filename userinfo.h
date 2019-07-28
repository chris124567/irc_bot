#ifndef USERINFO_H
#define USERINFO_H
struct user {
	char *nick1;
	char *nick2;
	char *nick3;
	char *username;
	char *realname;
}user;

struct user *init_user(struct user *info);
void cleanup_user(struct user *info);
int check_user(struct user *info);
#endif /* USERINFO_H */