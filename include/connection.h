/// @file connection.ch
/// @author Alexander Wallace
/// 

#ifndef CONNECTION_H
#define CONNECTION_H


// Standard Linux Libs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <ifaddrs.h>
#include <stdbool.h>

#include "error.h"

/// Struct proteting all information for listening thread
typedef struct {
    int fd; ///< File descripter for the listening port
} ThreadData;

/// prototypes
int open_listening_port(char* port);
void process_connections(int fdServer);
void* listen_for_messages(void* arg);

#endif // CONNECTION_H