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

#include "htable.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <limits.h>

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


#define ROTL32(x, y) ((x << y) | (x >> (32 - y)))

/* Globals */
static uint32_t hash_func_seed = 5381;

/*
 * Private Methods
 */
static void ht_reset(struct _ht *t)
{
        t->size = 0;
        t->used = 0;
        t->sizemask = 0;
        t->entries = NULL;
}

static void _ht_free(HashTable *ht, struct _ht *table)
{
        unsigned long i;

        for (i = 0; i < table->size && table->used > 0; i++) {
                HashEntry *e, *next;

                e = table->entries[i];
                if (e == NULL)
                        continue;

                while (e) {
                        next = e->next;

                        ht->props->key_free_fn(e->key);
                        ht->props->val_free_fn(e->val);
                        mt_free(e);

                        table->used--;
                        e = next;
                } /* while() */
        }         /* for() */

        mt_free(table->entries);
        ht_reset(table);
}

/*
 * Public Methods
 */

/*
 * This is an implementation of the mururmur3 hash by Austin Appleby:
 * https://github.com/aappleby/smhasher
 */
unsigned int murmur3_hash_32(const void *key, int len)
{
        uint32_t hash = hash_func_seed;
        const int nblocks = len / 4;
        const uint32_t *blocks = (const uint32_t *)key;
        const uint8_t *data = (const uint8_t *)key;
        int i;
        uint32_t k = 0;
        const uint8_t *tail;

        /* constants */
        uint32_t c1 = 0xcc9e2d51;
        uint32_t c2 = 0x1b873593;
        uint32_t n = 0xe6546b64;
        /* rotations */
        uint32_t r1 = 15;
        uint32_t r2 = 13;
        /* multiplicant */
        uint32_t m = 5;


        /* Body */
        for (i = 0; i < nblocks; i++) {
                uint32_t k1 = blocks[i];
                k1 *= c1;
                k1 = ROTL32(k1, r1);
                k1 *= c2;

                hash ^= k1;
                hash = ROTL32(hash, r2);
                hash = hash*m+n;
        }

        /* Tail */
        tail = (const uint8_t *)(data + nblocks * 4);
        switch (len & 3) {
        case 3: k ^= tail[2] << 16;
        case 2: k ^= tail[1] << 8;
        case 1: k ^= tail[0];
                k *= c1;
                k = ROTL32(k, r1);
                k *= c2;
                hash ^= k;
        }

        /* Finalisation */
        hash ^= len;
        hash ^= (hash >> 16);
        hash *= 0x85ebca6b;
        hash ^= (hash >> 13);
        hash *= 0xc2b2ae35;
        hash ^= (hash >> 16);

        return hash;
}

void ht_set_hash_function_seed(uint32_t seed)
{
        hash_func_seed = seed;
}

uint32_t ht_get_hash_function_seed(void)
{
        return hash_func_seed;
}


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


void ht_free(HashTable *ht)
{
        _ht_free(ht, &ht->table[0]);
        _ht_free(ht, &ht->table[1]);

        ht->props = NULL;
        ht->rehash_index = -1;

        mt_free(ht);
}

int ht_insert(HashTable *ht, void *key, void *val)
{
}

int ht_delete(HashTable *ht, void *key)
{
}

void *ht_lookup(HashTable *ht, void *key)
{
        return NULL;
}

int ht_replace(HashTable *ht, void *key, void *newval)
{
}
