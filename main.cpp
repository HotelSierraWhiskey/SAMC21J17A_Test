#include "samc21j17a.h"


#define A 0
#define B 1


int main() {

    port_registers_t port_register;             // port register API struct

    port_register.GROUP[A].PORT_DIRSET |= (1 << 0x13);    // set PA19 to output

    port_register.GROUP[A].PORT_OUTSET |= (1 << 0x13);    // set PA19 high
    
    while(1) {

    }

}