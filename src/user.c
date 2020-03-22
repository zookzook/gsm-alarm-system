//
//  user.c
//  gsm-alarm
//
//  Created by Michael Maier on 21.07.19.
//

#include "user.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>

#define ADMINS_DB "/home/debian/data/admins.conf"
#define RECIPIENTS_DB "/home/debian/data/recipients.conf"

PHONEBOOK admins;
PHONEBOOK recipients;

static void _clean(PHONEBOOK *phonebook) {
    
    uint8_t i = 0;
    while(i < phonebook->size ) {
        free(phonebook->users[i].number);
        phonebook->users[i].number = NULL;
        i += 1;
    }
    phonebook->size = 0;
}

static bool _load(PHONEBOOK* phonebook, char* filename) {
    
    bool result = false;
    FILE *fptr = fopen(filename, "r");
    
    if(fptr) {

        char line[80];
        
        _clean(phonebook);

        uint8_t i       = 0;
        while(fgets(line, 80, fptr) && i < MAX_USERS) {
            
            USER* user = &phonebook->users[i];
            size_t n = strlen(line);
            if(n > 1) {
                if(line[n-1] == '\n') {
                    line[n - 1] = '\0'; // skip new line
                    user->number = malloc(n);
                } // if
                else {
                    user->number = malloc(n + 1);
                } // else
                strcpy(user->number, line);
                i += 1;
            } // if
        }
        phonebook->size = i;
        result = true;
    } // if
    
    return result;
}

static bool _write_phonebook(PHONEBOOK* phonebook, char* filename) {
    
    bool result = false;
    
    FILE *output= fopen(filename, "wb");
    if(output) {
        
        uint8_t i = 0;
        while(i < phonebook->size ) {
            if(strlen(phonebook->users[i].number) > 0) {
                fprintf(output, "%s\n", phonebook->users[i].number);
            } // if
            i += 1;
        } // while
        fflush( output );
        fclose( output );
        
        result = true;
    } // if
    
    return result;
}

static bool _add_user(PHONEBOOK* phonebook, char* user, char* file) {
    
    bool result = false;
    if(phonebook->size < MAX_USERS) {
        
        USER *u = &phonebook->users[phonebook->size];
        size_t n = strlen(user);
        u->number = malloc(n + 1);
        strcpy(u->number, user);
        phonebook->size += 1;
        result = _write_phonebook(phonebook, file);
        
    }
    
    return result;
}

static bool _remove_user(PHONEBOOK* phonebook, char* user, char* file) {
    
    bool result = false;
    
    uint8_t i = 0;
    while(i < phonebook->size && !result) {
        if(strcmp(phonebook->users[i].number, user) == 0) {
            free(phonebook->users[i].number);
            phonebook->users[i].number[0] = '\0';
            result = true;
        } // if
        
        i += 1;
    }
    
    if(result) {
        result = _write_phonebook(phonebook, file);
    }
    
    return result;
}

static void user_dump_phonebook(PHONEBOOK* phonebook) {
    
    uint8_t i = 0;
    while(i < phonebook->size ) {
        info("Phonebook: %d : '%s'", i, phonebook->users[i].number);
        i += 1;
    }
}

bool user_load(void) {
    bool result = _load(&admins, ADMINS_DB) && _load(&recipients, RECIPIENTS_DB);
    
    info("User: admins:");
    user_dump_phonebook(&admins);
    
    info("User: recipients:");
    user_dump_phonebook(&recipients);
    
    return result;
}

bool user_isAdmin(char* user) {
    
    bool result = false;
    
    uint8_t i = 0;
    while(i < admins.size && !result) {
        result = strcmp(admins.users[i].number, user) == 0;
        i += 1;
    }
    return result;
}

bool user_add_admin(char* user) {
    
    bool result = false;
    if(_add_user(&admins, user, ADMINS_DB)) {
        info("User: new admins:");
        user_dump_phonebook(&admins);

        result = true;
    }
    
    return result;
}

bool user_remove_admin(char* user) {

    bool result = false;
    
    if(_remove_user(&admins, user, ADMINS_DB)) {

        info("User: new admins:");
        user_dump_phonebook(&admins);
        result = true;
    }
    
    return result;
}

bool user_add_recipient(char* user) {
    
    bool result = false;
    
    if(_add_user(&recipients, user, RECIPIENTS_DB)) {
        info("User: new recipients:");
        user_dump_phonebook(&recipients);
        result = true;
    }
    
    return result;

}

bool user_remove_recipient(char* user) {
    
    bool result = false;
    
    if(_remove_user(&recipients, user, RECIPIENTS_DB)) {
        
        info("User: new recipients:");
        user_dump_phonebook(&recipients);
        result = true;
    }
    
    return result;
}
