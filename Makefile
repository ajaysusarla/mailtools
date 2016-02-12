CC = gcc

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

EXTRA_CFLAGS = -Wall -Wextra -pedantic
LIBS =
CFLAGS = $(DEBUG) $(EXTRA_CFLAGS) $(OSFLAGS)

all: list-folders

list-folders: list-folders.c
	$(CC) $(CFLAGS) -c list-folders.c
	$(CC) $(CFLAGS) $(LIBS) \
		list-folders.o \
		-o list-folders

# config
conf: conf.c conf.h tests/conf-test.c
	$(CC) $(CFLAGS) -c conf.c
	$(CC) $(CFLAGS) -c tests/conf-test.c
	$(CC) $(CFLAGS) $(LIBS) \
		conf-test.o \
		conf.o \
		-o tests/conf-test

clean:
	rm -rf *.o \
		list-folders \
		tests/conf-test

.PHONY: check-syntax

check-syntax:
	$(CC) $(CFLAGS) -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
