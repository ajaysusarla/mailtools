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

#include "hash.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define PRIME_MOD 2147483647

struct _hashEntry {
        void *key;
        void *val;
        struct _hashEntry *next;
};

struct _ht {
        unsigned long size;     /* unsigned long: 0 to 4,294,967,295 */
        unsigned long used;
        unsigned long sizemask;
        struct _hashEntry **entries;
};

struct _hashTable {
        long rehash_index;
        unsigned long iters;
        HashProps *props;
        struct _ht table[2];
};

static unsigned int string_hash_fn(const unsigned char *str, unsigned int len)
{
        unsigned int h = 0;
}

static int string_cmp_fn(const char *a, const char *b)
{
        return strcmp(ENSURE_NON_NULL(a), ENSURE_NON_NULL(b));
}

/*
*********************
** Private methods **
*********************
*/

/* The hash table's size is based on the power of two. */
static unsigned long find_next_power(unsigned long size)
{
        unsigned long i = 2;

        if (size >= LONG_MAX)
                return LONG_MAX;

        while (1) {
                if (i >= size)
                        return i;
                i *= 2;
        }
}

static void ht_reset(struct _ht *t)
{
        t->size = 0;
        t->used = 0;
        t->sizemask = 0;
        t->entries = NULL;
}

/* Incremental rehash in 'steps'. */
static int ht_rehash(HashTable *ht, int steps)
{
        if (ht->rehash_index != -1)
                return 0;

        while (steps-- && ht->table[0].used != 0) {
                HashEntry *e, *next;

                /* Do nothing with empty entries */
                while (ht->table[0].entries[ht->rehash_index] == NULL)
                        ht->rehash_index++;

                e = ht->table[0].entries[ht->rehash_index];

                /* Move keys */
                while (e) {
                        unsigned int hash;

                        next = e->next;

                        /* Get index in the new hash table */
                        hash = ht->props->hash_fn(e->key) & ht->table[1].sizemask;
                        e->next = ht->table[1].entries[hash];
                        ht->table[1].entries[hash] = e;
                        ht->table[0].used--;
                        ht->table[1].used++;
                        e = next;
                } /* while() */

                ht->table[0].entries[ht->rehash_index] = NULL;
                ht->rehash_index++;
        } /* while() */

        /* Are we done rehashing? */
        if (ht->table[0].used == 0) {
                mt_free(ht->table[0].entries);
                ht->table[0] = ht->table[1];
                ht_reset(&ht->table[1]);
                ht->rehash_index = -1;
                return 0;
        }

        return 1;
}

static void ht_rehash_if_possible(HashTable *ht)
{
        if (ht->iters == 0)
                ht_rehash(ht, 1);
}

static int ht_resize(HashTable *ht, unsigned long size)
{
        struct _ht t;
        unsigned long newsize;

        if (ht->rehash_index != -1 || ht->table[0].used > size)
                return 1;

        newsize = find_next_power(size);
        if (newsize == ht->table[0].size)
                return 1;

        t.size = newsize;
        t.sizemask = newsize - 1;
        t.entries = mt_calloc(newsize, sizeof(HashEntry));
        t.used = 0;

        /* A new table */
        if (ht->table[0].entries == NULL) {
                ht->table[0] = t;
                return 0;
        }

        /* Resizing an existing table */
        ht->table[1] = t;
        ht->rehash_index = 0;

        return 0;
}

static int ht_resize_if_needed(HashTable *ht)
{
        if (ht->rehash_index != -1)
                return 0;

        if (ht->table[0].size == 0)
                ht_resize(ht, 4);

        if (ht->table[0].used >= ht->table[0].size) {
                return ht_resize(ht, ht->table[0].size*2);
        }

        return 0;
}

static int hash_table_get_index(HashTable *ht, void *key)
{
        unsigned int index = -1;
        int hash;

        if (ht_resize_if_needed(ht) != 0) {
                return -1;
        }

        hash = ht->props->hash_fn(key);// & ht->table[1].sizemask;
        

        return index;
}

static HashEntry *hash_table_add_key(HashTable *ht, void *key)
{
        int index;
        HashEntry *e;

        if (ht->rehash_index != -1) {
                ht_rehash_if_possible(ht);
        }

        index = hash_table_get_index(ht, key);
        if (index == -1)
                return NULL;

        e = mt_malloc(sizeof(HashEntry));

        return e;
}

static void hash_table_set_val(HashTable *ht, void *key, void *val)
{
}

/*
********************
** Public methods **
********************
*/

HashTable *ht_new(HashProps *props)
{
        HashTable *ht = NULL;

        ht = mt_malloc(sizeof(HashTable));

        ht_reset(&ht->table[0]);
        ht_reset(&ht->table[1]);

        ht->props = props;
        ht->rehash_index = -1;

        return ht;
}

int ht_add(HashTable *ht, void *key, void *val)
{
        HashEntry *e;

        e = hash_table_add_key(ht, key);

        if (!e)
                return -1;

        hash_table_set_val(ht, key, val);

        return 0;
}
