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

#include "conf.h"
#include "environment.h"

#include <stdio.h>
#include <ctype.h>
#include <locale.h>

static int _get_char(FILE *f)
{
        int c = getc(f);

        if (c == '\r') {
                c = getc(f);
                if (c != '\n') {
                        if (c != EOF)
                                ungetc(c, f);
                        c = '\r';
                }
        }

        return c;
}

static int get_config_from_file(const char *filename, FILE *f)
{
        //struct config cfg;
        int comment = 0;

        for (;;) {
                int c = _get_char(f);

                if (c == EOF)
                        return 0;

                if (c == '\n') {
                        if (c == EOF)
                                return 0;
                        comment = 0;
                        printf("\n");
                        continue;
                }

                if (comment || isspace(c))
                        continue;

                if (c == '#') {
                        comment = 1;
                        continue;
                }

                if (c == '[') {
                        printf("Section name: ");
                        continue;
                }

                if (c == ']') {
                        printf("\n");
                        continue;
                }

                if (c == '=') {
                }

                if (!isprint(c)) {
                        printf(">> %c\n", c);
                        break;
                }

                printf("%c", c);
        }

        fprintf(stderr, "Bad config\n");

        return -1;
}

int get_config(const char *filename)
{
        int ret = -1;
        FILE *f;

        if (filename == NULL || *filename == '\0')
                filename = "kixmailrc";

        f = fopen(filename, "r");
        if (f) {
                flockfile(f);
                ret = get_config_from_file(filename, f);
                funlockfile(f);
                fclose(f);
        }

        return ret;
}

