CC = gcc

CWD := $(shell pwd)
# Platform
UNAME := $(shell $(CC) -dumpmachine 2>&1 | grep -E -o "linux|darwin")

ifeq ($(UNAME), linux)
OSFLAGS = -DLINUX
DEBUG = -ggdb
else ifeq ($(UNAME), darwin)
OSFLAGS = -DMACOSX
DEBUG = -g
else ifeq ($(UNAME), solaris)
OSFLAGS = -DSOLARIS
DEBUG = -g
endif

EXTRA_CFLAGS := -Wall -Wextra -pedantic
LIBS :=
CFLAGS := $(DEBUG) $(EXTRA_CFLAGS) $(OSFLAGS)
TEST_CFLAGS := $(CFLAGS) -I$(CWD)

all: list-folders

list-folders: list-folders.c net net-ssl account-info
	$(CC) $(CFLAGS) -c list-folders.c
	$(CC) $(CFLAGS) $(LIBS) \
		list-folders.o \
		net_socket.o \
		account_info.o \
		-o list-folders

# network
net: net_socket.h net_socket.c
	$(CC) $(CFLAGS) -c net_socket.c

net-ssl: net_ssl.h net_ssl.c
	$(CC) $(CFLAGS) -c net_ssl.c

# account-info
account-info: account_info.h account_info.c
	$(CC) $(CFLAGS) -c account_info.c


# hash table
htable: htable.h htable.c examples/example-hash.c tests/test-hash.c utils
	$(CC) $(CFLAGS) -c htable.c

	$(CC) $(TEST_CFLAGS) -c examples/example-hash.c
	$(CC) $(TEST_CFLAGS) $(LIBS) \
		example-hash.o \
		htable.o \
		utils.o \
		-o examples/example-hash

	$(CC) $(TEST_CFLAGS) -c tests/test-hash.c
	$(CC) $(TEST_CFLAGS) $(LIBS) \
		test-hash.o \
		htable.o \
		utils.o \
		-o tests/test-hash

# config
conf: conf.c conf.h examples/example-conf.c
	$(CC) $(CFLAGS) -c conf.c
	$(CC) $(CFLAGS) -c examples/example-conf.c
	$(CC) $(CFLAGS) $(LIBS) \
		conf-test.o \
		conf.o \
		-o examples/example-conf

utils: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -rf *.o core\
		list-folders \
		examples/example-conf \
		examples/example-hash \
		tests/test-hash

.PHONY: check-syntax

check-syntax:
	$(CC) $(CFLAGS) -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
