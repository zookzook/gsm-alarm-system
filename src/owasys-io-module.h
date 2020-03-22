//
//  owasys-io-module.h
//  fleetdevice
//
//  Created by Michael Maier on 25.10.17.
//

#ifndef owasys_io_module_h
#define owasys_io_module_h

#include <stdio.h>
#include <stdbool.h>

bool load_io_module( void );
void unload_io_module( void );
bool io_read_pin(unsigned char pin, bool *out);
bool io_read_all_pin(unsigned short int *out );
void io_pir_on(void);
void io_pir_off(void);

#endif /* owasys_io_module_h */
