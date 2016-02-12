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

#ifndef _CONF_ACCOUNT_H_
#define _CONF_ACCOUNT_H_

struct _configAccount {
        char *name;
        char *email;

        char *incoming_server_name;
        char *outgoing_server_name;

        unsigned short incoming_port;
        unsigned short outgoing_port;
};

typedef struct _configAccount ConfigAccount;

#endif  /* _CONF_ACCOUNT_H_ */
