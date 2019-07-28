#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "userinfo.h"
#include "util.h"

struct user *init_user(struct user *info) {
    info = malloc_wrapper(sizeof(*info)); /* dereference */
    info->nick1 = NULL;
    info->nick2 = NULL;
    info->nick3 = NULL;
    info->username = NULL;
    info->realname = NULL;
    return info;
}

void cleanup_user(struct user *info) {
    free(info);
    info = NULL;
}

int check_user(struct user *info) {
    if (!info->nick1 || !info->nick2 || !info->nick3) {
        die("Please define all nicknames and alternates");
    }
    if (strlen(info->nick1) > 9 || strlen(info->nick2) > 9 ||
        strlen(info->nick3) > 9) {
        fprintf(stderr,
                "Warning: nick1, nick2, or nick3 length exceeds amount "
                "described in specification\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}