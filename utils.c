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

#include "utils.h"

#include <stdio.h>

void *mt_malloc(size_t size)
{
        void *ptr = NULL;

        if (size == 0)
                return ptr;

        ptr = (void *)malloc(size);
        if (!ptr) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        return ptr;
}

void *mt_calloc(size_t nmemb, size_t size)
{
        void *ptr = NULL;

        if (!nmemb || !size)
                return ptr;

        if (((size_t) - 1) / nmemb <= size) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        ptr = (void *)calloc(nmemb, size);
        if (!ptr) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        return ptr;
}

void mt_free(void *ptr)
{
        if (ptr) {
                free(ptr);
                ptr = NULL;
        }
}
