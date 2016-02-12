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

#include "net_socket.h"
#include "net_ssl.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

#include <netinet/in.h>
#include <netdb.h>


#include <sys/socket.h>
#include <sys/select.h>


/* Raw Sockets */
int net_socket_raw_open(Session *session, int use_ipv6)
{
        int sockfd;

        struct addrinfo *res, *cur;
        struct addrinfo hints;

        memset(&hints, 0, sizeof(hints));

        if (use_ipv6)
                hints.ai_family = AF_UNSPEC;
        else
                hints.ai_family = AF_INET;

        hints.ai_socktype = SOCK_STREAM;
}
