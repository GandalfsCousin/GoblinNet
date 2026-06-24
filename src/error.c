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