// Command file for Goblin Net. A custom encrypted p2p connection service

//* Put in header file later, Will probably need all
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>

int main(int argc, char** argv)
{
    // Void unused vars
    (void) argc;
    (void) argv; 

    fprintf(stdout, "Welcome to Goblin Net");

    return 0;
}