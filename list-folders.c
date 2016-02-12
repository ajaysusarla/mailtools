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

#define returniffail(x) do { typeof(x) __x = (x); if (__x < 0) return (__x); } while(0)

int verbose = 0;

static void print_help(const char *name)
{
        printf("%s [OPTION]\n", basename((char *)name));
        printf("lists all folders of an IMAP account");
        printf("    -h, --help     print this help\n");
        printf("    -v, --version  increase verbosity of output\n");
}

struct arguments {
        int count;
};

static int parse_arguments(int argc, char **argv, struct arguments *args)
{
        static const struct option long_options[] = {
                { "config-file", required_argument, NULL, 'c' },
                { "verbose", no_argument, NULL, 'v' },
                { "help", no_argument, NULL, 'h' },
        };

        memset(args, 0, sizeof(*args));

        while (1) {
                int c;

                c = getopt_long(argc, argv, "c:vh", long_options, &optind);

                if (c == -1)
                        break;

                switch (c) {
                case 'c':
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

        return 0;
}

int main(int argc, char **argv)
{
        struct arguments args;

        returniffail(parse_arguments(argc, argv, &args));
        exit(EXIT_SUCCESS);
}
