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

#include "account_info.h"

#include <stdlib.h>
#include <string.h>

int account_info_new(const char *username, int namelen,
                     const char *server, int serverlen,
                     const char *port, int portlen,
                     AccountInfo **ainfo)
{
        if ( (username && *username) ||
             (server && *server) ||
             (port && *port)) {
                *ainfo = (AccountInfo *) malloc(sizeof(AccountInfo *));
                if (!*ainfo)
                        return -1;

                memset(*ainfo, 0, sizeof(**ainfo));

        }
}
