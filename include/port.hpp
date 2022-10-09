#ifndef _PORT_H_
#define _PORT_H_


/*
    SAMC20/C21 Family Data Sheet
    PORT - I/O Pin Controller
    Page 435
*/


#include "../samc21j17a.h"


extern port_registers_t *port = (port_registers_t *)PORT_BASE_ADDRESS;


//  PORT group macros
#define A 0
#define B 1

#define _PIN(pin)   (1 << pin)

//  Basic operation macros
#define set_pin_as_output(group, pin)   port->GROUP[group].PORT_DIRSET |= _PIN(pin)
#define set_pin_as_input(group, pin)    port->GROUP[group].PORT_DIRSET &= ~_PIN(pin)

#define pin_high(group, pin)            port->GROUP[group].PORT_OUT |= _PIN(pin)
#define pin_low(group, pin)             port->GROUP[group].PORT_OUT &= ~_PIN(pin)

#define read_pin(group, pin)            port->GROUP[group].PORT_IN & _PIN(pin)


#endif