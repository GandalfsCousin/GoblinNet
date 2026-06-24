/// @file connection.c
/// @author Alexander Wallace
/// Holds all socket connections and related functions for 

#include "connection.h"


/**
 * Controler function for opening and listening to specified port
 * @param port Port to listen on
 * @returns Port file descriptor for open port
 */
int open_listening_port(char* port)
{
    struct addrinfo* ai = 0;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // All inputs

    if ((getaddrinfo(NULL, port, &hints, &ai))) {
        freeaddrinfo(ai);
        exit_listen_port_error(port); // Could not determine address
    }

    // Create a socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        freeaddrinfo(ai);
        exit_listen_port_error(port);
    }

    // Allow address (port number) to be reused immediately
    int optVal = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(int))
            < 0) {
        freeaddrinfo(ai);
        exit_listen_port_error(port);
    }

    // Bind socket to address
    if (bind(listenfd, ai->ai_addr, sizeof(struct sockaddr)) < 0) {
        freeaddrinfo(ai);
        exit_listen_port_error(port);
    }

    // Indicate willingness to listen on socket - connections can now be queued
    if (listen(listenfd, SOMAXCONN) < 0) {
        freeaddrinfo(ai);
        exit_listen_port_error(port);
    }

    freeaddrinfo(ai);
    return listenfd;
}


// Note - string is not null terminated - we need the length also.
void process_connections(int fdServer)
{
    int fd;
    struct sockaddr_in fromAddr;
    socklen_t fromAddrSize;

    // Repeatedly accept connections and process data (capitalise)
    while (1) {
        fromAddrSize = sizeof(struct sockaddr_in);
        // Block, waiting for a new connection. (fromAddr will be populated
        // with address of client)
        fd = accept(fdServer, (struct sockaddr*)&fromAddr, &fromAddrSize);
        if (fd < 0) {
            perror("Error accepting connection");
            exit(1);
        }

        // Turn our client address into a hostname and print out both
        // the address and hostname as well as the port number
        char hostname[NI_MAXHOST];
        int error = getnameinfo((struct sockaddr*)&fromAddr, fromAddrSize,
                hostname, NI_MAXHOST, NULL, 0, 0);
        if (error) {
            fprintf(stderr, "Error getting hostname: %s\n",
                    gai_strerror(error));
        } else {
            printf("Accepted connection from %s (%s), port %d\n",
                    inet_ntoa(fromAddr.sin_addr), hostname,
                    ntohs(fromAddr.sin_port));
        }

        // send ping to client
        dprintf(fd, "PING\n");
        ThreadData* data = malloc(sizeof(ThreadData));
        data->fd = fd;
        pthread_t threadID;
        pthread_create(&threadID, NULL, listen_for_messages, data);
        pthread_detach(threadID);
    }
}

/**
 * Main thread function to listen to Goblin Net Port for messages
 * @param arg MUST pass in ThreadData*
 */
void* listen_for_messages(void* arg)
{
    int fd = (*(ThreadData*)arg).fd;
    free(arg);

    char buffer[1024];
    ssize_t numBytesRead;

    // Repeatedly read data arriving from client
    while ((numBytesRead = read(fd, buffer, 1024)) > 0) {
        // Print out to stdout
        // Note (int) numBytesRead is unsafe
        dprintf(STDOUT_FILENO, "Message: %.*s\n", (int) numBytesRead, buffer);
        fflush(stdout);
    }
    // error or EOF - client disconnected

    if (numBytesRead < 0) {
        // Error code got
        exit_read_thread_error();
    }

    // client has exited
    fflush(stdout);
    close(fd);
    return NULL;
}
