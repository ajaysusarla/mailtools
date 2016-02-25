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

unsigned int hash_fn(const void *keyp)
{
        unsigned long key = (unsigned long)keyp;

        key = murmur3_hash_32(&key, sizeof(key));

        key += ~(key << 15);
        key ^=  (key >> 10);
        key +=  (key << 3);
        key ^=  (key >> 6);
        key += ~(key << 11);
        key ^=  (key >> 16);

        return key;
}

int key_cmp_fn(const void *key1, const void *key2)
{
        unsigned long k1 = (unsigned long)key1;
        unsigned long k2 = (unsigned long)key2;

        return k1 == k2;
}

HashProps hash_props_long = {
        hash_fn,
        key_cmp_fn,
        NULL,
        NULL,
        NULL,
        NULL
};

int main(void)
{
        HashTable *ht;
        long i;

        ht = ht_new(&hash_props_long);
        if (ht == NULL) {
                fprintf(stderr, "Error creating a hash table!\n");
                exit(EXIT_FAILURE);
        }

        printf(">> Inserting...");
        for (i = 0; i < 100; i++) {
                ht_insert(ht, (void *)i, (void *)(i*10));
        }
        printf("  Done.\n");

        printf(">> Inserting duplicate: %d. Should return (%d).\n   Returned: %d\n",
               13, HT_ERROR, ht_insert(ht, (void *)13, (void *)(13*10)));

        printf("** %d:%d\n", (int)ht_get_capacity(ht), (int)ht_get_size(ht));

        printf("|| %d's value: %ld\n", 10, (long)ht_find(ht, (void*)10));
        printf("|| %d's value: %ld\n", 20, (long)ht_find(ht, (void*)20));
        printf("|| %d's value: %ld\n", 89, (long)ht_find(ht, (void*)89));
        printf("|| %d's value: %ld\n", 500, (long)ht_find(ht, (void*)500));

        printf("<> Replacing...");
        ht_replace(ht, (void *)10, (void *)999);
        ht_replace(ht, (void *)500, (void *)500);
        printf("  Done.\n");

        printf("<> Values after replacement:\n");
        printf("|| %d's value: %ld\n", 10, (long)ht_find(ht, (void*)10));
        printf("|| %d's value: %ld\n", 500, (long)ht_find(ht, (void*)500));

        printf("<< Deleting...");
        for (i = 0; i < 100; i++) {
                ht_delete(ht, (void *)i);
        }
        printf("  Done.\n");
        printf("** %d:%d\n", (int)ht_get_capacity(ht), (int)ht_get_size(ht));

        ht_free(ht);

        return 0;
}
