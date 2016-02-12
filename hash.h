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

#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h>

typedef struct _hashTable HashTable;
typedef struct _hashEntry HashEntry;
typedef struct _hashProps HashProps;

struct _hashProps {
        unsigned int (*hash_fn)(const void *key);
        int (*key_cmp_fn)(const char *a, const char *b);

        void *(*key_dup)(const void *key);
        void *(*val_dup)(const void *val);

        void (*key_free)(void *key);
        void (*val_free)(void *val);
};

HashTable *ht_new(HashProps *props);

#endif  /* _HASH_H_ */
