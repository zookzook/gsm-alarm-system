//
//  user.h
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#ifndef user_h
#define user_h

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_USERS 20

typedef struct {
    char* number;
} USER;

typedef struct {

    uint8_t size;
    USER    users[MAX_USERS];
    
} PHONEBOOK;

PHONEBOOK admins;
PHONEBOOK recipients;

bool user_load(void);

bool user_isAdmin(char* user);

bool user_add_admin(char* user);
bool user_remove_admin(char* user);

bool user_add_recipient(char* user);
bool user_remove_recipient(char* user);

#endif /* user_h */
