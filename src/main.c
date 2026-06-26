/// @file main.c
/// @author Alexander Wallace
/// Command file for Goblin Net. A custom encrypted p2p connection service

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

// Goblin net imports
#include "error.h"
#include "connection.h"

// Prototypes 
//* Tmp, will move to other files later most likely, need a slim main
char* parse_cli(int argc, char** argv);
char* fetch_ip();



int main(int argc, char** argv)
{
    // Fetch port
    char* port = parse_cli(argc, argv);
    display_loading_bar();
    display_goblin();
    fprintf(stdout, "Welcome to Goblin Net\n");
    int listeningPortFD = open_listening_port(port);
    char* pubIP = fetch_ip();
    fprintf(stdout, "You are connected to [%s:%s]\n", pubIP, port);

    // Open thread to listen to incoming messages and print to stdout
    //! not thread yet just static for testing
    process_connections(listeningPortFD);

    // Loop waiting for input from user, then send over port
    while (true){

    }
    
    // TODO: Clean up
    return EXIT_OK;
}


/**
 * Given CLI args check validity and call erros
 * ? "goblinnet [portnum]"
 * @param argc number of arguments in command line
 * @param argv vector of string pointers for command arguments
 * @returns Port forwarded port to listen on
 */
char* parse_cli(int argc, char** argv)
{
    if (argc != 2) {
        exit_usage_error();
    }

    // Port is not empty
    if (strcmp(argv[1], "") == 0) {
        exit_usage_error();
    }

    // TODO: Check if is a number
  

    return argv[1];
}


/**
 * Simple function to grab users IP for connections
 * * MOVE OUT OF MAIN LATER maybe?
 * @returns Public IP of the user
 */
char* fetch_ip()
{ 
    struct ifaddrs *addrs, *tmp;
    getifaddrs(&addrs);
    tmp = addrs;
    char* publicIP;

    while (tmp) 
    {
        // Find public address
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            if (strcmp(tmp->ifa_name, "eth0") == 0) {
                publicIP = inet_ntoa(pAddr->sin_addr);
            }
        }
        tmp = tmp->ifa_next;
    }
    freeifaddrs(addrs);
    return publicIP;
}