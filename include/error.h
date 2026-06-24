/// @file error.h
/// @author Alexander Wallace
/// 

#ifndef ERROR_H
#define ERROR_H

// Error codes for GoblinNet
typedef enum {
    EXIT_OK = 0, ///< No errors
    EXIT_USAGE_ERROR = 2, ///< Wrong usage 
} ExitStatus;


/// prototypes
void exit_usage_error();

#endif // ERROR_H