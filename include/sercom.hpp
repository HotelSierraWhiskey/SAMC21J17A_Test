#ifndef _SERCOM_H_
#define _SERCOM_H_


/*
    SAMC20/C21 Family Data Sheet
    SERCOM - Serial Communication Interface
    Page 484

    Related:
    SERCOM USART    Page 492
    SERCOM SPI      Page 528
    SERCOM I2C      Page 555
*/


/*
    
    The core clock is required to clock the SERCOM while working as a master.
    The slow clock is only required for certain functions. See specific mode chapters for details.
    These clocks must be configured and enabled in the Generic Clock Controller (GCLK) before using the SERCOM.
    The SERCOM bus clock (CLK_SERCOMx_APB) can be enabled and disabled in the Main Clock Controller. Refer to
    Peripheral Clock Masking for details and default status of this clock.
*/


#include "../samc21j17a.h"


//  Basic operation macros
// #define sercom_set_mode(mode) sercom_registers

sercom_registers_t sercom_registers;


#endif