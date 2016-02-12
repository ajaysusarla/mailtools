/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include <libgen.h>
#include <termios.h>

#define returniffail(x) do { typeof(x) __x = (x); if (__x < 0) return (__x); } while(0)

int verbose = 0;

/* http://www.gnu.org/software/libc/manual/html_node/getpass.html */

static ssize_t my_getpass(char **lineptr, size_t *n, FILE *stream)
{
  struct termios old, new;
  int nread;

  /* Turn echoing off and fail if we can’t. */
  if (tcgetattr(fileno(stream), &old) != 0)
    return -1;
  new = old;
  new.c_lflag &= ~ECHO;
  if (tcsetattr(fileno(stream), TCSAFLUSH, &new) != 0)
    return -1;

  /* Read the password. */
  nread = getline(lineptr, n, stream);
  if ((*lineptr)[nread - 1] == '\n') {
          (*lineptr)[nread - 1] = '\0';
          nread--;
  }

  /* Restore terminal. */
  (void) tcsetattr(fileno (stream), TCSAFLUSH, &old);

  return nread;
}

static void print_help(const char *name)
{
        printf("\n");
        printf("USAGE:\n");
        printf("%s [OPTION]\n", basename((char *)name));
        printf("lists all folders of an IMAP account\n");
        printf("    -h, --help     print this help\n");
        printf("    -v, --version  increase verbosity of output\n");
        printf("\n");
}

struct arguments {
        char *username;
        char *server;
        char *port;
};

static int parse_arguments(int argc, char **argv, struct arguments *args)
{
        static const struct option long_options[] = {
                { "config-file", required_argument, NULL, 'c' },
                { "username", required_argument, NULL, 'u' },
                { "server", required_argument, NULL, 's' },
                { "port", required_argument, NULL, 'p' },
                { "verbose", no_argument, NULL, 'v' },
                { "help", no_argument, NULL, 'h' },
        };

        memset(args, 0, sizeof(*args));
        args->username = NULL;
        args->server = NULL;
        args->port = NULL;

        while (1) {
                int c;

                c = getopt_long(argc, argv, "c:u:s:p:vh", long_options, &optind);

                if (c == -1)
                        break;

                switch (c) {
                case 'c':
                        break;
                case 'u':
                        args->username = strdup(optarg);
                        break;
                case 's':
                        args->server = strdup(optarg);
                        break;
                case 'p':
                        args->port = strdup(optarg);
                        break;
                case 'v':
                        verbose++;
                        break;
                case '?':
                case 'h':
                        print_help(argv[0]);
                        break;
                }
        }

        if (args->username == NULL || args->server == NULL || args->port == NULL) {
                fprintf(stderr, "Missing arguments!\n");
                print_help(argv[0]);
                return -EINVAL;
        }

        return 0;
}

int main(int argc, char **argv)
{
        struct arguments args;
        char *password = NULL;
        size_t passlen = 0;

        returniffail(parse_arguments(argc, argv, &args));

        printf("Username: %s\n", args.username);
        printf("Server  : %s\n", args.server);
        printf("Port    : %s\n", args.port);

        printf("Enter Password: ");
        passlen = my_getpass(&password, &passlen, stdin);

        printf("\n");
        printf("The password is: %s(%zu)\n", password, passlen);

        exit(EXIT_SUCCESS);
}
