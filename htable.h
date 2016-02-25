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

#ifndef _HTABLE_H_
#define _HTABLE_H_

#include <stdint.h>

typedef struct _hashTable HashTable;
typedef struct _hashEntry HashEntry;
typedef struct _hashProps HashProps;

struct _hashProps {
        unsigned int (*hash_fn)(const void *key);
        int (*key_cmp_fn)(const char *a, const char *b);

        void *(*key_dup_fn)(const void *key);
        void *(*val_dup_fn)(const void *val);

        void (*key_free_fn)(void *key);
        void (*val_free_fn)(void *val);
};

HashTable *ht_new(HashProps *props);
void ht_free(HashTable *ht);

int ht_insert(HashTable *ht, void *key, void *val);
int ht_delete(HashTable *ht, void *key);
HashEntry *ht_find(HashTable *ht, void *key);
int ht_replace(HashTable *ht, void *key, void *newval);

void ht_set_hash_function_seed(uint32_t seed);
uint32_t ht_get_hash_function_seed(void);
unsigned int murmur3_hash_32(const void *key, int len);


#endif  /* _HTABLE_H_ */
