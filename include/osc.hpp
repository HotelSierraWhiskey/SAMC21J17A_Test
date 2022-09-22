#ifndef _OSC_H_
#define _OSC_H_


/*
    SAMC20/C21 Family Data Sheet
    OSCCTRL - Oscillators Controller
    Page 190
*/


#include "../samc21j17a.h"


// Frequency Table (SAMC20 Datasheet p.217)
const extern uint8_t _48MHz =    0b0000;
const extern uint8_t _24MHz =    0b0001;
const extern uint8_t _16MHz =    0b0010;
const extern uint8_t _12MHz =    0b0011;
const extern uint8_t _9_6MHz =   0b0100;
const extern uint8_t _8MHz =     0b0101;
const extern uint8_t _6_86MHz =  0b0110;
const extern uint8_t _6MHz =     0b0111;
const extern uint8_t _5_33MHz =  0b1000;
const extern uint8_t _4_8MHz =   0b1001;
const extern uint8_t _4_36MHz =  0b1010;
const extern uint8_t _4MHz =     0b1011;
const extern uint8_t _3_69MHz =  0b1100;
const extern uint8_t _3_43MHz =  0b1101;
const extern uint8_t _3_2MHz =   0b1110;
const extern uint8_t _3MHz =     0b1111;


//  Basic operation macros
#define osc48m_enable()         oscctrl_registers.OSCCTRL_OSC48MCTRL |= OSCCTRL_OSC48MCTRL_ENABLE(1)
#define osc48m_disable()        oscctrl_registers.OSCCTRL_OSC48MCTRL |= OSCCTRL_OSC48MCTRL_ENABLE(0)
#define osc48m_set_freq(freq)   osctrl_registers.OSCTRL_OSC48MDIV |= freq


oscctrl_registers_t oscctrl_registers;


#endif