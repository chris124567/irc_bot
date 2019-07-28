#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include "client.h"
#include "util.h"

void __attribute__((noreturn)) die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void *malloc_wrapper(size_t size) {
    void *mem = malloc(size);
    if (mem == NULL) {
        die("Failed to allocate memory");
    }
    return mem;
}

int send_all(int fd, const void *_buf) {
    ssize_t ret;
    size_t len, len1;
    const uint8_t *buf;

    buf = _buf;

    len = strlen((char *)buf);
    len1 = len;

    while (len > 0) {
        ret = write(fd, buf, len);
        if (ret < 0) {
            if (errno != EINTR && errno != EAGAIN) return -1;
        } else if (ret == 0) {
            break;
        } else {
            buf += ret;
            len -= ret;
        }
    }
    return len1 - len;
}

int sendall_fmt(int sock, const char *fmt, ...) {
    char buf[MAX_MSG_SIZE];
    int send_len;
    va_list args;

    if (strlen(fmt) != 0) {
        va_start(args, fmt);
        send_len = vsprintf(buf, fmt, args);
        va_end(args);

        if (send_len > 512) {
            send_len = 512;
        }

        if (send_all(sock, buf) <= 0) {
            return -1;
        }

        return send_len;
    }
    return 0;
}
