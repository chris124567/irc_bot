#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serverinfo.h"
#include "util.h"

struct server *init_server(struct server *serv) {
    struct server *info;
    info = malloc_wrapper(sizeof(*serv)); /* dereference */
    info->ip = NULL;
    info->port = 0;
    info->channel = NULL;
    return info;
}

void cleanup_server(struct server *serv) {
    free(serv);
    serv = NULL;
}
