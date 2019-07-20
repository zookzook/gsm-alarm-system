#include "logger.h"

#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <syslog.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static bool daemonMode       = false;

void logger_open(bool newValue) {
    daemonMode = newValue;
    if(daemonMode) {
        openlog("alarm", LOG_PID, LOG_DAEMON);
    }
    closelog();
}

void logger_close(void) {
    if(daemonMode) {
        closelog();
    }
}

void info(const char *fmt, ...) {

    if(daemonMode) {
        va_list myargs;
        va_start(myargs, fmt);
        vsyslog(LOG_INFO, fmt, myargs);
        va_end(myargs);
    }
    else {
        pthread_mutex_lock(&mutex);
        
        time_t ltime;
        struct tm result;
        
        ltime = time(NULL);
        localtime_r(&ltime, &result);
        
        // pthread_t pid= pthread_self();
        
        // printf( "INFO  [%ld] %04d-%02d-%02d %02d:%02d:%02d - ", (long)pid, result.tm_year + 1900, result.tm_mon + 1, result.tm_mday, result.tm_hour, result.tm_min, result.tm_sec );
        
        /* Declare a va_list type variable */
        va_list myargs;
        
        /* Initialise the va_list variable with the ... after fmt */
        
        va_start(myargs, fmt);
        
        /* Forward the '...' to vprintf */
        vprintf(fmt, myargs);
        
        printf( "\n" );
        
        /* Clean up the va_list */
        va_end(myargs);
        
        pthread_mutex_unlock(&mutex);
    }
}

