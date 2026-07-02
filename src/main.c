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
#include "chatroom.h"
#include "commands.h"
#include "tui.h"

// Prototypes 
//* Tmp, will move to other files later most likely, need a slim main
void goblinnet_controler(UserInfo* userInfo);
UserInfo* parse_cli(int argc, char** argv);
char* fetch_ip();

int main(int argc, char** argv)
{
    UserInfo* userInfo = parse_cli(argc, argv);
    display_goblin();
    fprintf(stdout, "Welcome to Goblin Net\n");
    // Should hold user for majorit of time 
    goblinnet_controler(userInfo);

    free(userInfo);
    return EXIT_OK;
}

//! Can optimise code below by parsing execute command pointer and concat both controllers

/**
 * Conbtroller for non-chatroom interation
 * @param userInfo Information struct
 */
void goblinnet_controler(UserInfo* userInfo) 
{
    while (true) {
        // Get input
        char input[256];
        fprintf(stdout, "> ");

        if (fgets(input, sizeof(input), stdin) != NULL) {
            char* endPtr = strchr(input, '\n'); 
            if (endPtr == NULL) {
                // Not new line so buffer overun
                fprintf(stdout, "Message is too long.\n");
                fflush(stdout);
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { } // purge all stdin
                continue;
            } else {
                // Replace new line to truncate input and proccess
                *endPtr = '\0';
                proccess_command(input, userInfo);
            }
        } else {
            // Some error, should be fine to reloop?
            continue;
        }
    }
}




/**
 * Given CLI args check validity and creates UserInfo
 * ? "goblinnet [--name <name>]"
 * @param argc number of arguments in command line
 * @param argv vector of string pointers for command arguments
 * @returns updated UserInfo with name if given
 */
UserInfo* parse_cli(int argc, char** argv)
{
    int MINAGRS = 1;
    int MAXARGS = 3;
    if (argc < MINAGRS || argc > MAXARGS){
        // Too many or too few
        exit_usage_error();
    }

    UserInfo* userInfo = malloc(sizeof(UserInfo));
    userInfo->name = "User";

    if (argc != 1) {
        if (strcmp("--name", argv[1]) == 0 && argc == 3) {
            userInfo->name = argv[2];
        } else {
            // gibberish command
            exit_usage_error();
        }
    }

    return userInfo;
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