#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include "logger.h"

void logMsg(FILE* fd, uint8_t options, const char* proc, const char* message, va_list args){
    time_t timeVal;
    char timestamp[TIME_BUFFER];
    char datestamp[TIME_BUFFER];
    struct tm* tm_info;

    timeVal = time(NULL);
    tm_info = localtime(&timeVal);

    strftime(datestamp, TIME_BUFFER, "%F ", tm_info);
    strftime(timestamp, TIME_BUFFER, "%H:%M:%S ", tm_info);

    if(options & LOG_DATE)
        fprintf(fd, "%s", datestamp);
    if(options & LOG_TIME)
        fprintf(fd, "%s", timestamp);

    if(options & LOG_ERROR)
        fprintf(fd, "ERROR -- \"%s\": ", proc);
    if(options & LOG_INFO)
        fprintf(fd, "INFO -- \"%s\": ", proc);
    if(options & LOG_DEBUG)
        fprintf(fd, "DEBUG -- \"%s\": ", proc);

    vfprintf(fd, message, args);

    fprintf(fd, "\n");
}

void logError(FILE* fd, const char* proc, const char* message, ...){
    va_list args;
    
    va_start(args, message);
    logMsg(fd, LOG_DATE | LOG_TIME | LOG_ERROR, proc, message, args);
    va_end(args);
}

void logInfo(FILE* fd, const char* proc, const char* message, ...){
    va_list args;

    va_start(args, message);
    logMsg(fd, LOG_DATE | LOG_TIME | LOG_INFO, proc, message, args);
    va_end(args);
}

void logDebug(FILE* fd, const char* proc, const char* message, ...){
    va_list args;

    va_start(args, message);
    logMsg(fd, LOG_DATE | LOG_TIME | LOG_DEBUG, proc, message, args);
    va_end(args);
}