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

#ifndef _CONF_H_
#define _CONF_H_


typedef enum {
        C_TYPE_INT,
        C_TYPE_STRING,
        C_TYPE_BOOL
} confType;

struct _confEntry {
        char *name;
        char *val;
        confType type;
};

typedef struct _confEntry ConfEntry;

#endif  /* _CONF_H_ */
