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

#include "net_tcp.h"
#include "net_ssl.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <netdb.h>


#include <sys/socket.h>
#include <sys/select.h>


/* TCP Sockets */
int net_tcp_socket_read(int sockfd, char *buf, size_t len)
{
        int rv;

        rv = read(sockfd, buf, len);
        if (rv == -1) {
                perror("net_tcp_socket_read:read()");
        }

        return rv;
}

int net_tcp_socket_write(int sockfd, const char *buf, size_t len)
{
        int rv;

        rv = write(sockfd, buf, len);
        if (rv == -1) {
                perror("net_tcp_socket_write:write()");
        }

        return rv;
}

int net_tcp_socket_open(char *addr, int port, int use_ipv6)
{
        int sockfd = -1;
        struct addrinfo *sinfo, *s;
        struct addrinfo hints;
        char portstr[6];           /* strlen("65535") + 1 */
        int rv;

        memset(&hints, 0, sizeof(hints));

        if (use_ipv6)
                hints.ai_family = AF_UNSPEC;
        else
                hints.ai_family = AF_INET;

        hints.ai_socktype = SOCK_STREAM;

        snprintf(portstr, sizeof(portstr), "%d", port);

        rv = getaddrinfo(addr, portstr, &hints, &sinfo);
        if (rv != 0) {
                fprintf(stderr, "getaddrinfo(): %s", strerror(errno));
                return -1;      /* FIXME: Need to return correct errors. */
        }


        for (s = sinfo; s != NULL; s = s->ai_next) {
                sockfd = socket(s->ai_family, s->ai_socktype, s->ai_protocol);
                if (sockfd == -1)
                        continue;

                rv = connect(sockfd, s->ai_addr, s->ai_addrlen);
                if (rv == -1) {
                        close(sockfd);
                }

                fcntl(sockfd, F_SETFD, FD_CLOEXEC);
                break;

        } /* for */

        freeaddrinfo(sinfo);

        return sockfd;
}

int net_tcp_socket_close(int sockfd)
{
        return close(sockfd);
}
