# H1 Documentation for getting started with the Rills Automation Development Board v1.0

This documentation assumes you have:

-   a Rills Automation Development Board
-   a Black Magic Probe (BMP) device
-   Firmware for the BMP (with added SAMC21J17A target support)
-   GNU Arm Embedded Toolchain (gcc-arm-none-eabi) installed
-   dfu-utils installed
-   One or two other dependencies that might pop up of which you'll need to install the dev packages. It's been a long couple days, sorry.

We will be using the Black Magic Probe to program the dev board. The stock `blackmagic-native` BMP firmware does not support SAMC targets, which is the family of part our dev board uses. So, before we're able to program our development board we need to upload firmware that supports our part (the SAMC21J17A microcontroller) onto the BMP.

In order to do this we're going to use `dfu-util`, a tool for downloading and uploading firmware to/from devices over USB. You can also apparently use [bmputil](https://github.com/blackmagic-debug/bmputil), a similar tool written in rust. I already had `dfu-util` installed and it's what the kind people at [1 Bit Squared](https://1bitsquared.com/) recommend, so I'm going to use that.

So, first: Be sure that `arm-none-eabi-gcc` is on your path. This is compiler invoked by the makefile in the blackmagic project. If `arm-none-eabi-gcc` is in your home directory, for example, then you should `export PATH=~/gcc-arm-none-eabi-10.3-2021.10/bin:$PATH`

Compile the modified BMP firmware with `make`. The executable file you're after is `blackmagic.bin`. This is what we're going to upload onto the BMP. Make sure you have the BMP plugged in. The `dfu-util` line you want is `dfu-util -d 1d50:6018,:6017 -s 0x08002000:leave -D src/blackmagic.bin`. If `dfu-util` gives you uphill about DFU suffixes or not being able to open the DFU device, `sudo` the line.

Apparently `dfu-util` gets angry quite easily. It might tell you that it lost your device after a reset. Then you might realize the LEDs on your BMP are doing a little chaser dance. This will probably happen. Don't worry, you can't brick the probe. Unplug your BMP and hold down its little button and plug it back in to force the BMP into bootloader mode (that's what the LED chasing indicates) and try that `dfu-util` line again. If the last line of the resulting output reads `File downloaded successfully Transitioning to dfuMANIFEST state`, your BMP now supports our dev board part.
