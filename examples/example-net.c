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
 *
 *  Example program to demonstrate hashing using the htable.[hc] in mailtools.
 *
 *
 */

#include "net_tcp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOST "www.google.com"
#define PORT 80

#define BUF_SIZE 2048
#define SEND_CMD "GET\n"

int main(void)
{
        int sockfd;
        char buf[BUF_SIZE] = { 0 };

        sockfd = net_tcp_socket_open(HOST, PORT, 0);

        printf("Connecting to %s:%d...", HOST, PORT);
        if (!sockfd) {
                fprintf(stderr, "Error connecting to %s on %d", HOST, PORT);
                exit(EXIT_FAILURE);
        }
        printf("...Done!\n");

        printf("Writing...");
        net_tcp_socket_write(sockfd, SEND_CMD, strlen(SEND_CMD));
        printf("...Done!\n");

        printf("Reading...");
        net_tcp_socket_read(sockfd, buf, BUF_SIZE-1);
        printf("..Done!\n");
        printf("=======\n");
        printf("%s\n", buf);
        printf("=======\n");

        printf("Disconnecting from %s...", HOST);
        net_tcp_socket_close(sockfd);
        printf("...Done!\n");

        exit(EXIT_SUCCESS);
}
