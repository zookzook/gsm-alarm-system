#include "daemon.h"
#include "logger.h"
#include "owasys-io-module.h"
#include "owasys-rtu-module.h"
#include "owasys-gsm-module.h"
#include "d-sensors.h"
#include "watchdog.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

volatile bool gContinueRunning;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        info("Received SIGINT...exiting!");
        gContinueRunning= false;
    } // if
    else
        if( signo == SIGTERM ) {
            info("Received SIGTERM...exiting!");
            gContinueRunning= false;
        } // if
}

int daemonize(void) {
    
    /* Our process ID and Session ID */
    pid_t pid, sid;
    
    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
     we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    
    /* Change the file mode mask */
    umask(0);
    
    /* Open any logs here */
    
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }
    
    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }
    
    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    logger_open(true);
    
    /* Daemon-specific initialization goes here */
    
    loop();
    
    logger_close();
    
    exit(EXIT_SUCCESS);
}

void loop(void) {
    
    gContinueRunning = true;
    
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        info( "Unable to init sig_handler" );
    }
    if (signal(SIGTERM, sig_handler) == SIG_ERR) {
        info( "Unable to init sig_handler" );
    }
    
    load_rtu_module();
    load_io_module();
    gsm_load_module();
        
    sensors_running_loop();
    
    wd_shutdown();
    unload_io_module();
    gsm_unload_module();
    unload_rtu_module();

}
