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

#ifndef _NET_TCP_H_
#define _NET_TCP_H_

#include "net.h"

#include <stdio.h>

int net_tcp_socket_open(char *addr, int port, int use_ipv6);
int net_tcp_socket_close(int sockfd);
int net_tcp_socket_read(int sockfd, char *buf, size_t len);
int net_tcp_socket_write(int sockfd, const char *buf, size_t len);

#endif  /* _NET_TCP_H_ */
