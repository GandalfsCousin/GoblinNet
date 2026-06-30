/// @file connection.ch
/// @author Alexander Wallace
/// 

#ifndef COMMANDS_H
#define COMMANDS_H


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
#include "chatroom.h"

/// prototypes
void proccess_command(char* cmd, UserInfo* userInfo) ;
void command_help();
void command_host(int argc, char** argv, UserInfo* userInfo);


#endif // COMMANDS_H