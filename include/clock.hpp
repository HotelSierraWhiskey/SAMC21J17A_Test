#ifndef _CLOCK_H_
#define _CLOCK_H_


/*
    SAMC20/C21 Family Data Sheet
    GCLK - Generic Clock Controller
    Page 137
*/

#include "../samc21j17a.h"

/*  
    GLCK_IO pin mappings
    Using the GCLK I/O lines requires the I/O pins to be configured.
    If GENCTRLn.OE is 0, the according I/O pin is set to an Output Off Value, which is selected by GENCTRLn.OOV: If
    GENCTRLn.OOV is '0', the output clock will be low. If this bit is '1', the output clock will be high.

    PB14	GCLK_IO[0]
    PB22	GCLK_IO[0]
    PA27	GCLK_IO[0]
    PA28	GCLK_IO[0]
    PA30	GCLK_IO[0]
    PA14	GCLK_IO[0]
    PB23	GCLK_IO[1]
    PA15	GCLK_IO[1]
    PB15	GCLK_IO[1]
    PA16	GCLK_IO[2]
    PB16	GCLK_IO[2]
    PA17	GCLK_IO[3]
    PB17	GCLK_IO[3]
    PA20	GCLK_IO[4]
    PB10	GCLK_IO[4]
    PA10    GCLK_IO[4]
    PA11    GCLK_IO[5]
    PB11	GCLK_IO[5]
    PA21	GCLK_IO[5]
    PB12	GCLK_IO[6]
    PA22	GCLK_IO[6]
    PA23	GCLK_IO[7]
    PB13	GCLK_IO[7]
*/



//  Basic operation macros

#define clock_enable(n)             gclk_registers.GCLK_GENCTRL[n] |= GCLK_GENCTRL_GENEN(1)
#define clock_disable(n)            gclk_registers.GCLK_GENCTRL[n] |= GCLK_GENCTRL_GENEN(0)

#define clock_output_enable(n)      gclk_registers.GCLK_GENCTRL[n] |= GCLK_GENCTRL_OE(1)
#define clock_output_disable(n)     gclk_registers.GCLK_GENCTRL[n] |= GCLK_GENCTRL_OE(0)

#define set_clock_OOV_high()        gclk_registers.GCLK_GENCTRL[n] |= GCLK_GENCTRL_OOV(1)
#define set_clock_OOV_low()         gclk_registers.GCLK_GENCTRL[n] |= GCLK_GENCTRL_OOV(0)

//  SERCOM Core Clock utilities (PCHCTRL Peripheral Channel Control, Page: 151)
//  The core clock is required to clock the SERCOM while working as a master. 
//  The slow clock is only required for certain functions. See specific mode chapters for details.

#define GCLK_SERCOM0_CORE 19
#define GCLK_SERCOM1_CORE 20
#define GCLK_SERCOM2_CORE 21
#define GCLK_SERCOM3_CORE 22
#define GCLK_SERCOM4_CORE 23
#define GCLK_SERCOM5_CORE 25

extern constexpr uint8_t get_sercom_peripheral_channel_index(uint8_t sercom) {
    switch (sercom) {
        case 0: return GCLK_SERCOM0_CORE;
        case 1: return GCLK_SERCOM1_CORE;
        case 2: return GCLK_SERCOM2_CORE;
        case 3: return GCLK_SERCOM3_CORE;
        case 4: return GCLK_SERCOM4_CORE;
        case 5: return GCLK_SERCOM5_CORE;
    }
}

#define enable_sercom_core_clock(sercom)  gclk_registers.GCLK_PCHCTRL[get_sercom_peripheral_channel_index(sercom)] |= GCLK_PCHCTRL_CHEN(1) 
#define disable_sercom_core_clock(sercom) gclk_registers.GCLK_PCHCTRL[get_sercom_peripheral_channel_index(sercom)] |= GCLK_PCHCTRL_CHEN(0)

//  SERCOM Bus Clock utilities (MCLK Main Clock Controller, Page: 154)
//  The SERCOM bus clock (CLK_SERCOMx_APB) can be enabled and disabled in the Main Clock Controller.
//  Refer to Peripheral Clock Masking for details and default status of this clock.

extern constexpr uint8_t get_sercom_APB_bit(uint8_t sercom, uint8_t value) {
    switch (sercom) {
        case 0: return MCLK_APBCMASK_SERCOM0(value);
        case 1: return MCLK_APBCMASK_SERCOM1(value);
        case 2: return MCLK_APBCMASK_SERCOM2(value);
        case 3: return MCLK_APBCMASK_SERCOM3(value);
        case 4: return MCLK_APBCMASK_SERCOM4(value);
        case 5: return MCLK_APBCMASK_SERCOM5(value);
    }
}

#define enable_sercom_bus_clock(sercom) mclk_registers.MCLK_APBCMASK |= get_sercom_APB_bit(sercom, 1)
#define disable_sercom_bus_clock(sercom) mclk_registers.MCLK_APBCMASK |= get_sercom_APB_bit(sercom, 0)


extern gclk_registers_t gclk_registers;

extern mclk_registers_t mclk_registers;


#endif