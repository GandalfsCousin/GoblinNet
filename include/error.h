/// @file error.h
/// @author Alexander Wallace
/// 

#ifndef ERROR_H
#define ERROR_H

#include <pthread.h>

// Error codes for GoblinNet
typedef enum {
    EXIT_OK = 0, ///< No errors
    EXIT_USAGE_ERROR = 2, ///< Wrong usage 
    EXIT_LISTENING_ERROR = 3, ///< Error listening to port
    EXIT_THREAD_READ_ERROR = 11 ///< ONLY FOR THREADS, couldnt read input from file
} ExitStatus;


/// prototypes
void exit_usage_error();
void exit_listen_port_error(char* port);
void exit_read_thread_error();

#endif // ERROR_H