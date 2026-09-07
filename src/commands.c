/// @file commands.c
/// @author Alexander Wallace
/// Holds all commands controlers 


#include "commands.h"


/**
 * Given a command, it will proccess the command and execute it
 * @param command 
 */
void proccess_command(char* cmd, UserInfo* userInfo) 
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
        command_help();
    } else if (strcmp(cmdv[0], "exit") == 0) {
        free(cmdv);
        exit(0);
    } else if (strcmp(cmdv[0], "host") == 0) {
        command_host(cmdc, cmdv, userInfo);
    } else if (strcmp(cmdv[0], "join") == 0) {
        connect_to_server(cmdc, cmdv);
    } else {
        // bad
        fprintf(stdout, "Please enter a valid command, or help for list of commands.\n");
        fflush(stdout);
    }

    free(cmdv);
}

/**
 * Help command for the main menu
 */
void command_help()
{
    fprintf(stdout, "Commands:\n");
    fprintf(stdout, "`host <port> [--name <name>] [--password <password>]`: Creates a chatroom.\n");
    fprintf(stdout, "`join <ip> <port>`: Joins established chatroom.\n");
    fprintf(stdout, "`exit`: exits the program.\n");
    fflush(stdout);
} 


/**
 * Sets up a chat room, will hold user
 * Moves user to chat room -> opens listen port -> accepts connections and moved them to the chat room
 * Currently all -> host; host -> all, later use host as broadcast to other users (psuedo-server)
 * ? `host <port> [--name <name>] [--password <password>]`
 */
void command_host(int argc, char** argv, UserInfo* userInfo)
{
    // Extract information
    bool validCmds = false;
    char* name = "Chatroom";
    char* password = "";
    char* port;
    for (int i = 1; i < argc; i++){
        // first arg always port
        if (i == 1){
            //! CHECK IF IT IS A VALID NUM
            port = argv[i];
            validCmds = true;
            continue;
        }
        if (strcmp("--name", argv[i]) == 0) {
            i++;
            if (i >= argc) {
                // no room
                validCmds = false;
                break;
            }
            if (strncmp("-", argv[i], 1) == 0) {
                fprintf(stderr, "Invalid name: \"%s\"\n", argv[i]);
                validCmds = false;
                break;
            } else
            validCmds = true;
            name = argv[i];
        } else if (strcmp("--password", argv[i]) == 0) {
            i++;
            if (i >= argc) {
                // no room
                validCmds = false;
                break;
            }
            if (strncmp("-", argv[i], 1) == 0) {
                fprintf(stderr, "Invalid password: \"%s\"\n", argv[i]);
                validCmds = false;
                break;
            } else
            validCmds = true;
            password = argv[i];
        } else {
            fprintf(stderr, "Invalid command: \"%s\"\n", argv[i]);
            validCmds = false;
            break;
        }
    
    }

    if (!validCmds) {
        fprintf(stderr, "Failed to start chatroom\n");
        fprintf(stderr, "Usage: `host <port> [--name <name>] [--password <password>]`\n");
        fflush(stderr);
        return;
    }

    // Valid
    int listedFD = open_listening_port(port);


    fprintf(stdout, "----------/ Connected to %s \\----------\n", name);
    fflush(stdout);
    // loop for chatting
    chatroom_controler(userInfo);
} 



/**
 * Sets up a chat room, will hold user
 * Moves user to chat room -> opens listen port -> accepts connections and moved them to the chat room
 * Currently all -> host; host -> all, later use host as broadcast to other users (psuedo-server)
 * ? `host <port> [--name <name>] [--password <password>]`
 */
void command_join(int argc, char** argv, UserInfo* userInfo)
{
    // Extract information
    bool validCmds = false;
    char* name = "Chatroom";
    char* password = "";
    char* port;
    for (int i = 1; i < argc; i++){
        // first arg always port
        if (i == 1){
            //! CHECK IF IT IS A VALID NUM
            port = argv[i];
            validCmds = true;
            continue;
        }
        if (strcmp("--name", argv[i]) == 0) {
            i++;
            if (i >= argc) {
                // no room
                validCmds = false;
                break;
            }
            if (strncmp("-", argv[i], 1) == 0) {
                fprintf(stderr, "Invalid name: \"%s\"\n", argv[i]);
                validCmds = false;
                break;
            } else
            validCmds = true;
            name = argv[i];
        } else if (strcmp("--password", argv[i]) == 0) {
            i++;
            if (i >= argc) {
                // no room
                validCmds = false;
                break;
            }
            if (strncmp("-", argv[i], 1) == 0) {
                fprintf(stderr, "Invalid password: \"%s\"\n", argv[i]);
                validCmds = false;
                break;
            } else
            validCmds = true;
            password = argv[i];
        } else {
            fprintf(stderr, "Invalid command: \"%s\"\n", argv[i]);
            validCmds = false;
            break;
        }
    
    }

    if (!validCmds) {
        fprintf(stderr, "Failed to start chatroom\n");
        fprintf(stderr, "Usage: `host <port> [--name <name>] [--password <password>]`\n");
        fflush(stderr);
        return;
    }

    // Valid
    int listedFD = open_listening_port(port);


    fprintf(stdout, "----------/ Connected to %s \\----------\n", name);
    fflush(stdout);
    // loop for chatting
    chatroom_controler(userInfo);
} 