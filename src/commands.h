//
//  subscriber.h
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#ifndef commands_h
#define commands_h

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Ping: liefert den aktuellen Status zurück
 */
void cmd_ping(char *sender);

/**
 * Boot: liefert den aktuellen Status zurück und meldet einen Boot-Vorgang
 */
void cmd_boot(void);

/**
 * Stellt die Zähler für SMS-Sender zurück
 */
void cmd_reset(char *sender);

void cmd_sensor_change(uint8_t sensorIndex, bool newValue);

void cmd_pir_detected(uint8_t pirIndex);

/**
 * Lock/Unlock
 */
void cmd_lock(char *sender);
void cmd_unlock(char *sender);

/**
 * User-Management
 */
void cmd_add_admin(char *sender, char *admin);
void cmd_remove_admin(char *sender, char *admin);

void cmd_add_recipient(char *sender, char *recipient);
void cmd_remove_recipient(char *sender, char *recipient);

#endif /* commands_h */
