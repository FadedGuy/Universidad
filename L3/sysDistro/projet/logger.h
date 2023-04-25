#ifndef LOGGER
#define LOGGER

#include <stdint.h>
#include <stdarg.h>

// Log options
#define LOG_DATE    0x01 //0b00000001
#define LOG_TIME    0x02 //0b00000010

#define LOG_ERROR   0x04 //0b00000100
#define LOG_INFO    0x08 //0b00001000
#define LOG_DEBUG   0x10 //0b00010000

#define TIME_BUFFER 30


/**
 * Logs a message to a FILE with the given options
 * @param fd File that will be written to
 * @param options Flags indicating the information and type of log it is
 * @param proc Identifier from which the log originated
 * @param message Formatted message to write
 * @param args Arguments for formatted message if any
 * @note It is recommended to use the preset for each level rather than this one.
*/
void logMsg(FILE* fd, uint8_t options, const char* proc, const char* message, va_list args);

/**
 * Logs an error message to FILE
 * @param fd File that will be written to
 * @param proc Identifier from which the log originated
 * @param message Formatted message to write
 * @param ... Arguments for message if any
*/
void logError(FILE* fd, const char* proc, const char* message, ...);

/**
 * Logs information to FILE
 * @param fd File that will be written to
 * @param proc Identifier from which the log originated
 * @param message Formatted message to write
 * @param ... Arguments for message if any
*/
void logInfo(FILE* fd, const char* proc, const char* message, ...);

/**
 * Logs debug information to FILE
 * @param fd File that will be written to
 * @param proc Identifier from which the log originated
 * @param message Formatted message to write
 * @param ... Arguments for message if any
*/
void logDebug(FILE* fd, const char* proc, const char* message, ...);

#endif