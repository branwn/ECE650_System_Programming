/*
** client.c -- a stream socket client demo
*/


#ifndef TCP_SOCKET_HOT_POTATO_SOCKET_CLIENT_H
#define TCP_SOCKET_HOT_POTATO_SOCKET_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <stdbool.h>

// get a in_addr
void *get_in_addr_c(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// set up a client
int client_setup(char * hostname, char* port) {
    setbuf(stdout,NULL);
    int sockfd;

    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(hostname, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        fprintf(stderr, "\thostname: %s\n", hostname);
        fprintf(stderr, "\tport: %s\n", port);
        exit (1);
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(sockfd);
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return (2);
    }
    inet_ntop(p->ai_family, get_in_addr_c((struct sockaddr *) p->ai_addr),
              s, sizeof s);
    freeaddrinfo(servinfo); // all done with this structure
    return sockfd;
}

// close the client
int client_close (int sockfd) {
    return close(sockfd);
}



#endif //TCP_SOCKET_HOT_POTATO_SOCKET_CLIENT_H
