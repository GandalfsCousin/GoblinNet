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
#include "tui.h"

/// Struct holding all information related to the user
typedef struct {
    char* name;
    char* port;
} UserInfo;


// Prototypes 
//* Tmp, will move to other files later most likely, need a slim main
void goblinnet_controler(UserInfo* userInfo);
void proccess_command(char* cmd);
UserInfo* parse_cli(int argc, char** argv);
char* fetch_ip();

int main(int argc, char** argv)
{
    UserInfo* userInfo = parse_cli(argc, argv);
    fprintf(stdout, "Welcome to Goblin Net\n");
    goblinnet_controler(userInfo);
    // Open thread to listen to incoming messages and print to stdout
    //! not thread yet just static for testing

    // Loop waiting for input from user, then send over port

    // TODO: Clean up
    return EXIT_OK;
}

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
                proccess_command(input);
            }
        } else {
            // Some error, should be fine to reloop?
            continue;
        }
    }
}


/**
 * processes the given chat command
 * @param command 
 */
void proccess_command(char* cmd) 
{
    // tokenise command
    char** cmdv = malloc(sizeof(char*));
    char* token = strtok(cmd, " ");
    int cmdc = 0;
    while (token != NULL) {
        cmdv = realloc(cmdv, sizeof(char*) * (cmdc+1));
        cmdv[cmdc++] = token;
        token = strtok(NULL, " ");
    }
    // cmdc & cmdv can be used for easy command parsing

    if (strcmp(cmdv[0], "help") == 0) {
        fprintf(stdout, "Commands:\n");
        fprintf(stdout, "`host <port> [--name <name>] [--password <password>]`: Creates a chatroom.\n");
        fprintf(stdout, "`join <ip> <port>`: Joins established chatroom.\n");
        fprintf(stdout, "`exit`: exits the program.\n");
    } else if (strcmp(cmdv[0], "exit") == 0) {
        free(cmdv);
        exit(0);
    } else {
        // bad
        fprintf(stdout, "Please enter a valid command, or help for list of commands.\n");
    }

    free(cmdv);
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