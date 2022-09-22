#ifndef _PORT_H_
#define _PORT_H_


/*
    SAMC20/C21 Family Data Sheet
    PORT - I/O Pin Controller
    Page 435
*/


#include "../samc21j17a.h"


//  PORT group macros
#define A 0
#define B 1

#define PIN(pin)   (1 << pin)

//  Basic operation macros
#define set_pin_as_output(group, pin)   port_register.GROUP[group].PORT_DIRSET |= PIN(pin);
#define set_pin_as_input(group, pin)    port_register.GROUP[group].PORT_DIRSET &= ~PIN(pin);
  
#define set_pin_high(group, pin)        port_register.GROUP[group].PORT_OUTSET |= PIN(pin);
#define set_pin_low(group, pin)         port_register.GROUP[group].PORT_OUTCLR |= PIN(pin);

#define read_pin(group, pin)            port_register.GROUP[group].PORT_IN & PIN(pin)

port_registers_t port_register;


#endif