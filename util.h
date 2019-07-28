#ifndef UTIL_H
#define UTIL_H
#include <stdarg.h>
void __attribute__((noreturn)) die(const char * msg);
void *malloc_wrapper(size_t size);
int send_all(int fd, const void *_buf);
int sendall_fmt(int sock, const char *fmt, ...);
#endif /* UTIL_H */