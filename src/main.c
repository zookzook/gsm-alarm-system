#include "owasys-io-module.h"
#include "owasys-rtu-module.h"
#include "owasys-gsm-module.h"
#include "logger.h"
#include "d-sensors.h"
#include "watchdog.h"
#include "notify.h"
#include "user.h"
#include "commands.h"
#include "loop.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/reboot.h>
#include <signal.h>

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

bool init_all(void) {
    
    if(!wd_init())
        return false;
    
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        info( "Unable to init sig_handler" );
        return false;
    } // if
    if (signal(SIGTERM, sig_handler) == SIG_ERR) {
        info( "Unable to init sig_handler" );
        return false;
    } // if
    
    wd_ping();
    
    user_load();
    
    loop_load_state();
    
    if(!load_rtu_module()) {
        return false;
    } // if
    if(!load_io_module()) {
        return false;
    } // if
    if(!gsm_load_module()){
        return false;
    } // if

    load_switches();
    init_pirs();
    
    io_pir_off();
    
    // todo better
    gsm_start_worker();
    
    gsm_init();
    
    return gsm_start();
}
void reboot_now(void) {
    
    sync();
    if(reboot(RB_AUTOBOOT) != 0) {
        info("Unable to reboot");
    }
}


void send_sms() {
    gsm_init();
    
    int ret = gsm_start();
    if(ret == 0) {
        
        info("GSM is running");
        
        bool active = gsm_is_active();
        info("GSM is active %d", active);
        gsm_send_sms("004916090984428", "Hello World");
    }
    else {
        info("GSM not running %d", ret);
    }
    
    gsm_stop();

}

void cleanup(void) {
    unload_io_module();
    gsm_unload_module();
    unload_rtu_module();
}

int main (int argc, char *argv[]) {
    
    int result = EXIT_FAILURE;
    
    setbuf(stdout, NULL);
    
    info("Starting GSM Alarm System");

    if(init_all()) {
        notify_ready();
        cmd_boot();
        run_loop();
        notify_stopping();
        result = EXIT_SUCCESS;
    } // if
    else {
        notify_failure();
        result = EXIT_FAILURE;
    } // else
    
    cleanup();
    
    exit(result);
}

