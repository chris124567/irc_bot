CFLAGS := -ansi -std=c89
#CFLAGS += -ggdb -O1 -g
CFLAGS += -march=native -Ofast #-fuse-linker-plugin -flto=4 -s
CFLAGS += -pedantic -Wall -Wextra -Wshadow -Wnull-dereference -Wduplicated-branches -Wundef -Wstrict-prototypes -Wsign-conversion -Wno-unused-parameter -Wconversion
CFLAGS += -D_FORTIFY_SOURCE=2 -Wformat=2 -Wstrict-overflow=5
#CFLAGS += -DDEBUG
CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer -fmerge-all-constants -Wl,--build-id=none -Wl,--gc-sections -Wa,--noexecstack
CC := c89
FILES := util.c connect.c userinfo.c client.c serverinfo.c
SOURCE := ircc

all:
	${CC} ${CFLAGS} ${FILES} ${SOURCE}.c -o ${SOURCE}

clean:
	rm ${SOURCE}
