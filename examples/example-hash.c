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
 *
 *  Example program to demonstrate hashing using the htable.[hc] in mailtools.
 *
 *
 */

#include "htable.h"

#include <stdio.h>
#include <stdlib.h>

HashProps hash_props_long = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
};

int main(void)
{
        HashTable *ht;

        ht = ht_new(&hash_props_long);

        if (ht == NULL) {
                fprintf(stderr, "Error creating a hash table!\n");
                exit(EXIT_FAILURE);
        }

        ht_free(ht);

        return 0;
}
