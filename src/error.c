/// @file error.c
/// @author Alexander Wallace
/// Error Functions for Goblin Net

#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Exit handler for invalid command given, exit with 2
 */
void exit_usage_error()
{
    fprintf(stderr, "Usage ./goblinnet [Port Number]\n");
    exit(EXIT_USAGE_ERROR);
}

/**
 * Exit handler for if unable to listen on main port, exit with 3
 * @param port The given port to listen to
 */
void exit_listen_port_error(char* port)
{
    fprintf(stderr, "Goblin Net: unable to listen on port \"%s\".\n", port);
    exit(EXIT_LISTENING_ERROR);
}

/**
 * Exit handler for thread when failing to read from file
 * ONLY use with non-main thread.
 */
void exit_read_thread_error()
{
    fprintf(stderr, "Goblin Net: error recieiving message.\n");
    pthread_exit((void*) EXIT_THREAD_READ_ERROR);
}
