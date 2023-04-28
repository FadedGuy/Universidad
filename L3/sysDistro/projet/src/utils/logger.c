#include <time.h>

#include "logger.h"

void logMsg(FILE* fd, uint8_t options, const char* proc, const char* file, const int line, const char* message, va_list args){
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
        fprintf(fd, "ERROR -- %s:%d in funtion: \"%s\": ", file, line, proc);
    if(options & LOG_INFO)
        fprintf(fd, "INFO -- %s:%d in funtion: \"%s\": ", file, line, proc);
    if(options & LOG_DEBUG)
        fprintf(fd, "DEBUG -- %s:%d in funtion: \"%s\": ", file, line, proc);

    vfprintf(fd, message, args);

    fprintf(fd, "\n");
}

void logErrorMessage(FILE* fd, const char* func, const char* file, int line, const char* message, ...){
    va_list args;

    va_start(args, message);
    logMsg(fd, LOG_DATE | LOG_TIME | LOG_ERROR, func, file, line, message, args);
    va_end(args);
}

void logInfoMessage(FILE* fd, const char* func, const char* file, int line, const char* message, ...){
    va_list args;

    va_start(args, message);
    logMsg(fd, LOG_DATE | LOG_TIME | LOG_INFO, func, file, line, message, args);
    va_end(args);
}

void logDebugMessage(FILE* fd, const char* func, const char* file, int line, const char* message, ...){
    va_list args;

    va_start(args, message);
    logMsg(fd, LOG_DATE | LOG_TIME | LOG_DEBUG, func, file, line, message, args);
    va_end(args);
}
