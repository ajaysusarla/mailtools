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

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>

void *mt_malloc(size_t size);
void *mt_calloc(size_t nmemb, size_t size);
void mt_free(void *ptr);

#define ENSURE_NON_NULL(p) p?p:""

#endif  /* _UTILS_H_ */
