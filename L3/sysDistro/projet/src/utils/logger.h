#ifndef LOGGER
#define LOGGER

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

// Log options
#define LOG_DATE    0x01 //0b00000001
#define LOG_TIME    0x02 //0b00000010

#define LOG_ERROR   0x04 //0b00000100
#define LOG_INFO    0x08 //0b00001000
#define LOG_DEBUG   0x10 //0b00010000

#define TIME_BUFFER 30

/**
 * Logs an error message to stderr
 * @param message Message to show
 * @note The use of this function is recommended over logErrorMessage if writing to stderr, if log is 
 * any other file, its management is let to the user
*/
#define logError(message) logErrorMessage(stderr, __func__, __FILE__, __LINE__, message)

/**
 * Logs an error message to stderr
 * @param message Message to show
 * @param ... Arguments for formatted message
 * @note The use of this function is recommended over logErrorMessage if writing to stderr, if log is 
 * any other file, its management is let to the user
*/
#define logErrorWithArgs(message, ...) logErrorMessage(stderr, __func__, __FILE__, __LINE__, message, __VA_ARGS__)

/**
 * Logs an info message to stdout
 * @param message Message to show
 * @note The use of this function is recommended over logInfoMessage if writing to stdout, if log is 
 * any other file, its management is let to the user
*/
#define logInfo(message) logInfoMessage(stdout, __func__, __FILE__, __LINE__, message)

/**
 * Logs an info message to stdout
 * @param message Message to show
 * @param ... Arguments for formatted message
 * @note The use of this function is recommended over logInfoMessage if writing to stdout, if log is 
 * any other file, its management is let to the user
*/
#define logInfoWithArgs(message, ...) logInfoMessage(stdout, __func__, __FILE__, __LINE__, message, __VA_ARGS__)

/**
 * Logs a debug message to stdout
 * @param message Message to show
 * @note The use of this function is recommended over logDebugMessage if writing to stdout, if log is 
 * any other file, its management is let to the user
*/
#define logDebug(message) logDebugMessage(stdout, __func__, __FILE__, __LINE__, message)

/**
 * Logs a debug message to stdout
 * @param message Message to show
 * @param ... Arguments for formatted message
 * @note The use of this function is recommended over logDebugMessage if writing to stdout, if log is 
 * any other file, its management is let to the user
*/
#define logDebugWithArgs(message, ...) logDebugMessage(stdout, __func__, __FILE__, __LINE__, message, __VA_ARGS__)

/**
 * Logs a message to a FILE with the given options
 * @param fd File that will be written to
 * @param options Flags indicating the information and type of log it is
 * @param proc Identifier from which the log originated 
 * @param message Formatted message to write
 * @param args Arguments for formatted message if any
 * @note It is recommended to use the preset for each level rather than this one.
 * @note For proc, file and line you can use the defined macros
 * *__func__ Supported on most compilers with C99
 * *__FILE__ Always supported
 * *__LINE__ Always supported
*/
void logMsg(FILE* fd, uint8_t options, const char* proc, const char* file, const int line, const char* message, va_list args);

/**
 * Logs an error message to FILE
 * @param fd File that will be written to
 * @param func Function that called the logger
 * @param file File in which the function is defined
 * @param line Line in which the logger is called
 * @param message Formatted message to write
 * @param ... Arguments for message if any
*/
void logErrorMessage(FILE* fd, const char* func, const char* file, int line, const char* message, ...);

/**
 * Logs an information message to FILE
 * @param fd File that will be written to
 * @param func Function that called the logger
 * @param file File in which the function is defined
 * @param line Line in which the logger is called
 * @param message Formatted message to write
 * @param ... Arguments for message if any
*/
void logInfoMessage(FILE* fd, const char* func, const char* file, int line, const char* message, ...);

/**
 * Logs a debug message to FILE
 * @param fd File that will be written to
 * @param func Function that called the logger
 * @param file File in which the function is defined
 * @param line Line in which the logger is called
 * @param message Formatted message to write
 * @param ... Arguments for message if any
*/
void logDebugMessage(FILE* fd, const char* func, const char* file, int line, const char* message, ...);


#endif