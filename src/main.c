#include "daemon.h"
#include "owasys-io-module.h"
#include "owasys-rtu-module.h"
#include "owasys-gsm-module.h"
#include "logger.h"
#include "d-sensors.h"
#include "watchdog.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/reboot.h>
#include <signal.h>
#include <systemd/sd-daemon.h>

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


int main (int argc, char *argv[]) {
    
    setbuf(stdout, NULL);
    
    // waiting for rtu system
    info("Starting GSM Alarm System");

    bool dontWait = false;
    bool fork = false;
    
    int opt;
    while ((opt = getopt (argc, argv, "sf")) != -1)  {
        switch (opt) {
            case 's':
                dontWait = true;
                break;
            case 'f':
                fork = true;
                break;
        }
    }
    
    if(fork) {
        if(!dontWait) {
            info("Waiting for 30s");
            sleep(30);
        } // if
        daemonize();
    }
    else {

        wd_init();
        
        if (sd_notify(0, "READY=1")<0){
            info("Systemd WD startup error");
        } // if
        else {
            info("Systemd WD started");
        } // else
        
        loop();
        
        if (sd_notify(0, "STOPPING=1")<0){
            info("Error stopping watchdog service");
        }
        
        info("Finished");

    }
    
    
    // reboot
}

void reboot_now(void) {
    
    sync();
    if(reboot(RB_AUTOBOOT) != 0) {
        info("Unable to reboot");
    }
}
