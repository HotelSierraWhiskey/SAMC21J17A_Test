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


//  Registers
sercom_registers_t *sercom_0 = (sercom_registers_t *)SERCOM0_BASE_ADDRESS;
sercom_registers_t *sercom_1 = (sercom_registers_t *)SERCOM1_BASE_ADDRESS;
sercom_registers_t *sercom_2 = (sercom_registers_t *)SERCOM2_BASE_ADDRESS;
sercom_registers_t *sercom_3 = (sercom_registers_t *)SERCOM3_BASE_ADDRESS;
sercom_registers_t *sercom_4 = (sercom_registers_t *)SERCOM4_BASE_ADDRESS;
sercom_registers_t *sercom_5 = (sercom_registers_t *)SERCOM5_BASE_ADDRESS;


//  SERCOM mode macros
#define MODE_USART_EXTERNAL_CLOCK   0x0
#define MODE_USART_INTERNAL_CLOCK   0x1
#define MODE_SPI_SLAVE              0x2
#define MODE_SPI_MASTER             0x3
#define MODE_I2C_SLAVE              0x4
#define MODE_I2C_MASTER             0x5


constexpr sercom_registers_t *get_sercom(uint8_t n) {
    switch(n) {
        case 0: return sercom_0;
        case 1: return sercom_1;
        case 2: return sercom_2;
        case 3: return sercom_3;
        case 4: return sercom_4;
        case 5: return sercom_5;
    }
}

//  Basic operations
constexpr void set_sercom_mode(uint8_t sercom, uint8_t mode) {
    sercom_registers_t *sercom_register = get_sercom(sercom);
    switch(mode) {
        case MODE_USART_EXTERNAL_CLOCK: sercom_register->USART_EXT.SERCOM_CTRLA |= MODE_USART_EXTERNAL_CLOCK; // these are incorrect, use sercom.h macros
        case MODE_USART_INTERNAL_CLOCK: sercom_register->USART_INT.SERCOM_CTRLA |= MODE_USART_INTERNAL_CLOCK;
        case MODE_SPI_SLAVE: sercom_register->SPIS.SERCOM_CTRLA |= MODE_SPI_SLAVE;
        case MODE_SPI_MASTER: sercom_register->SPIM.SERCOM_CTRLA |= MODE_SPI_MASTER;
        case MODE_I2C_SLAVE: sercom_register->I2CS.SERCOM_CTRLA |= MODE_I2C_SLAVE;
        case MODE_I2C_MASTER: sercom_register->I2CM.SERCOM_CTRLA |= MODE_I2C_MASTER;
    }
}

/*


• Control B register (CTRLB), except the Receiver Enable (RXEN) and Transmitter Enable (TXEN) bits.
• Baud register (BAUD)
When the USART is enabled or is being enabled (CTRLA.ENABLE=1), any writing attempt to these registers will be
discarded. If the peripheral is being disabled, writing to these registers will be executed after disabling is completed.
Enable-protection is denoted by the "Enable-Protection" property in the register description.
Before the USART is enabled, it must be configured by these steps:
X   1. Select either external (0x0) or internal clock (0x1) by writing the Operating Mode value in the CTRLA register 
(CTRLA.MODE).
X   2. Select either asynchronous (0) or or synchronous (1) communication mode by writing the Communication
Mode bit in the CTRLA register (CTRLA.CMODE).
X   3. Select pin for receive data by writing the Receive Data Pinout value in the CTRLA register (CTRLA.RXPO).
X    4. Select pads for the transmitter and external clock by writing the Transmit Data Pinout bit in the CTRLA register
(CTRLA.TXPO).
X   5. Configure the Character Size field in the CTRLB register (CTRLB.CHSIZE) for character size.
X   6. Set the Data Order bit in the CTRLA register (CTRLA.DORD) to determine MSB- or LSB-first data
transmission.
?   7. To use parity mode:
?   7.1. Enable parity mode by writing 0x1 to the Frame Format field in the CTRLA register (CTRLA.FORM).
?   7.2. Configure the Parity Mode bit in the CTRLB register (CTRLB.PMODE) for even or odd parity.
X   8. Configure the number of stop bits in the Stop Bit Mode bit in the CTRLB register (CTRLB.SBMODE).
X   9. When using an internal clock, write the Baud register (BAUD) to generate the desired baud rate.
X   10. Enable the transmitter and receiver by writing '1' to the Receiver Enable and Transmitter Enable bits in the
CTRLB register (CTRLB.RXEN and CTRLB.TXEN)


*/




#endif