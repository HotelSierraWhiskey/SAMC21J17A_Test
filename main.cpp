#include "samc21j17a.h"
#include "include/osc.hpp"
#include "include/clock.hpp"
#include "include/port.hpp"
#include "include/sercom.hpp"



void sercom_debug_uart_init(void) {

	sercom_3->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE(0);

	enable_sercom_bus_clock(3);			// <-- from clock.hpp
	enable_sercom_core_clock(3);		// <-- from clock.hpp

	set_pin_as_output(B, 22);			// <-- from port.hpp (sercom_3/ sercom_5 pin)
	set_pin_as_input(B, 23);			// <-- from port.hpp (sercom_3/ sercom_5 pin)

	// set_sercom_mode(3, MODE_USART_INTERNAL_CLOCK);	// <-- from sercom.hpp

	sercom_3->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_MODE(MODE_USART_INTERNAL_CLOCK);

	sercom_3->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_CMODE(0); // async mode

	sercom_3->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_TXPO(0); // PAD0 for TX
	sercom_3->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_RXPO(1); // PAD1 for RX

	sercom_3->USART_INT.SERCOM_CTRLB |= SERCOM_USART_INT_CTRLB_CHSIZE(0); // 8-bit char size

	sercom_3->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_DORD(0); // MSB trasmitted first (change to 1 for LSB)

	sercom_3->USART_INT.SERCOM_CTRLB |= SERCOM_USART_INT_CTRLB_SBMODE(0); // 1 stop bit

	sercom_3->USART_INT.SERCOM_BAUD |= 65208; // 15.01kHz Fbaud at 48mhz serial engine frequency

	sercom_3->USART_INT.SERCOM_CTRLB |= SERCOM_USART_INT_CTRLB_TXEN(1); // transmitter enable
	sercom_3->USART_INT.SERCOM_CTRLB |= SERCOM_USART_INT_CTRLB_RXEN(1); // receiver enable

	sercom_3->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE(1);
}

/*

Data Transmission

Data transmission is initiated by writing the data to be sent into the DATA register. Then, the data in TxDATA will be
moved to the shift register when the shift register is empty and ready to send a new frame. After the shift register is
loaded with data, the data frame will be transmitted.

When the entire data frame including stop bit(s) has been transmitted and no new data was written to DATA, the
Transmit Complete interrupt flag in the Interrupt Flag Status and Clear register (INTFLAG.TXC) will be set, and the
optional interrupt will be generated.

The Data Register Empty flag in the Interrupt Flag Status and Clear register (INTFLAG.DRE) indicates that the
register is empty and ready for new data. The DATA register should only be written to when INTFLAG.DRE is set.

*/


void sercom_debug_uart_tx_char(char c) {

	while ((sercom_3->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE(0)) != 0) {	// wait if register isn't empty
		;
	}

	sercom_3->USART_INT.SERCOM_DATA = c;
}




int main() {

	osc48m_set_freq(_48MHz);
	osc48m_enable();

	clock_mclk_set_source(GCLK_GENCTRL_SRC_OSC48M);
	clock_mclk_set_div(GCLK_GENCTRL_DIVSEL_DIV1_Val);
	clock_PORT_enable();
	clock_mclk_enable();

	set_pin_as_output(A, 19);
	pin_high(A, 19);

	sercom_debug_uart_init();

    while(1) {

		sercom_debug_uart_tx_char('U');
		// pin_high(A, 19);

		// for (uint16_t i = 0; i < 60000; i++) {

		// }
		
		// pin_low(A, 19);

		// for (uint16_t i = 0; i < 60000; i++) {
			
		// }
		

    }

}

#include <cstdint>
#include <array>
// #include "platform.hxx"

[[gnu::naked]] void irqReset() noexcept;
void irqNMI() noexcept;
void irqEmptyDef() noexcept;
[[gnu::naked]] void irqHardFault() noexcept;

extern const uint32_t stackTop;
extern const uint32_t endText;
extern uint32_t beginData;
extern const uint32_t endData;
extern uint32_t beginBSS;
extern const uint32_t endBSS;

using ctorFuncs_t = void (*)();
extern const ctorFuncs_t beginCtors, endCtors;

using irqFunction_t = void (*)();

struct nvicTable_t final
{
	const void *stackTop;
	std::array<irqFunction_t, 155> vectorTable;
};

[[gnu::section(".nvic_table"), gnu::used]] static const nvicTable_t nvicTable
{
	&stackTop,
	{
        irqReset, /* Reset handler */
		irqNMI, /* NMI handler */
		irqHardFault, /* Hard Fault handler */

		/* Configurable priority handlers */
		irqEmptyDef, /* MMU Fault handler */
		irqEmptyDef, /* Bus Fault handler */
		irqEmptyDef, /* Usage Fault */
		nullptr, /* Reserved */
		nullptr, /* Reserved */
		nullptr, /* Reserved */
		nullptr, /* Reserved */
		irqEmptyDef, /* SV Call */
		irqEmptyDef, /* Debug Monitor */
		nullptr, /* Reserved */
		irqEmptyDef, /* Pending SV */
		irqEmptyDef, /* Sys Tick */

        /* Vendor specific handlers */
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
		irqEmptyDef,
	}
};


void irqReset() noexcept
{
    while (true)
    {
        auto *src{&endText};
        for (auto *dst{&beginData}; dst < &endData; ++dst, ++src)
            *dst = *src;
        for (auto *dst{&beginBSS}; dst < &endBSS; ++dst)
            *dst = 0;
        for (auto *ctor{&beginCtors}; ctor != &endCtors; ++ctor)
            (*ctor)();

        main();
    }
}


void irqNMI() noexcept
{
	while (true);
}

void irqHardFault() noexcept
{
	/* Get some information about the fault for the debugger.. */
	__asm__(R"(
		movs	r0, #4
		movs	r1, lr
		tst		r0, r1
		beq		_MSP
		mrs		r0, psp
		b		_HALT
	_MSP:
		mrs		r0, msp
	_HALT:
		ldr     r1, [r0, #0x00] /* r0 */
		ldr     r2, [r0, #0x04] /* r1 */
		ldr     r3, [r0, #0x08] /* r2 */
		ldr     r4, [r0, #0x0C] /* r3 */
		ldr     r5, [r0, #0x10] /* r12 */
		ldr     r6, [r0, #0x14] /* lr */
		ldr     r7, [r0, #0x1C] /* xpsr */
		mov     r8, r7
		ldr     r7, [r0, #0x18] /* pc */
		bkpt    #0
	_DEADLOOP:
		b		_DEADLOOP
	)");
	/* The lowest 8 bits of r8 (xpsr) contain which handler triggered this, if there is a signal handler frame before this. */
}

void irqEmptyDef() noexcept
{
	while (true);
}



/*   

irqNMI is for Non-Maskable Interrupts.. the's really only one reason one 
of those can happen here, and it means something catastrophic has occurred, so the single 
line routine just traps it so you'll see the program stop and be able to attach GDB and go "oh"

irqEmptyDef also traps but with a different function name so you can distinguish it from irqNMI in gdb - 
good way to know if you enabled the right interrupt handler

once in the function there's no way out without tripping a higher priority (higher up the table) vector handler
so the only way out of irqNMI is to trip irqReset

irqHardFault() is for when you've written something that causes the CPU to, well.. hard fault - 
for example, accessing a register for a peripheral that's not currently powered up, 
or trying to access a byte below the bottom of RAM (0x1fffffff) which would indicate running out of stack

the way the assembly code in the function works is to figure out if the processor's in privileged mode or not 
(it is by default) to load the correct stack pointer (mrs r0,psp (privileged) vs mrs r0,msp)
once it's done that it then loads the crash data from the stck into r1 through r8
(easier to info regs than have to manually dump the stack yourself)

and then triggers a hardware breakpoint if there's a debugger attached (bkpt #0) and enters an infinite loop 
just like what those while (true) loops translate to, trapping the processor

*/