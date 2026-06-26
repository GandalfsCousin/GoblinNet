/// @file tui.c
/// @author Callum Smith
/// Terminal UI components for Goblin Net

// Source - https://stackoverflow.com/q/20947161
// Posted by qweruiop, modified by community. See post 'Timeline' for change history
// Retrieved 2026-06-26, License - CC BY-SA 3.0

#include <stdio.h>
#include <unistd.h>

void display_loading_bar(){
    int i = 0;
    for (i = 0; i < 10000; i++){
        printf("\rLoading Goblinnet %d", i/100);
        fflush(stdout);
        usleep(500);
    }
    printf("\r                    ");
    printf("\n");
    fflush(stdout);
}

void display_goblin(){
    printf("░░▄█▀░░░░░░░░░░░░░░░░░░░░░░▀▀█▄░");
    printf("▄█▀░░░░░░░░░░░░░░░░░░░░░░░░░░░▀█");
    printf("█▀░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▀");
    printf("▀░░░░░░░░░░░░░░░░░▄▄▄▄▄░░░░░░░░░");
    printf("░░░░░░░░░▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀░░░░");
    printf("░░░░░░░▄▄▄▄▄▄▄▄▄░░░░░░▄▄▄▄▄▄▄▄▄░");
    printf("░░░░░░██▀▀▀▀▀▀███░░░▄░▀██▀▀▀▀▀██");
    printf("░░░░░░██░██░░░███░░██░░██░░██░██");
    printf("░░░░░░▀█▄▄▄▄▄███░░░██░░▀█▄▄▄▄▄█▀");
    printf("░░░░░░░▀████▀▀▀░░░░██▄░░▀▀███▀░░");
    printf("██▀▀▀░░░░░░░░░░░░░░░░░░░░░░░░░░░");
    printf("▀░░▄░░░░░▄▄▄▄▄▄▄▄░░░▄▄▄▄▄▄░░░▄█░");
    printf("░░░▀▀█▄▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀██▀░░░");
    printf("█▄░░░░░▀▀▀██████▀▀▀▀▀█████▀░░░░▄");
    printf("░▀█▄░░░░░░░░░░░░▄▄▄░░░░░░░░░░░▄▀");
    printf("░░░▀██▄░░░░░░░░░░▄█░░░░░░░░▄▄█▀░");
}