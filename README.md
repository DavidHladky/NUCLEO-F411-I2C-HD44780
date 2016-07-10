# NUCLEO-F411 I2C HD44780
This project presents a library for controlling display HD44780, which is connected to the development board NUCLEO STM32F411. Display is connected to the STM32 thought I2C 8bit IO expander PCF8574A. The main routine are placed in the file HD44780.c. 
In the file HD44780.h are located definitions of functions and commands. The main function is an example of using this library for controlling HD44780. The latest files are hal.c i2c and i2c hal.h that carry out setting the I2C peripherals STM32F411.

## Description of functions in the file HD44780.c
* Basic initialization of HD44780 performs function which is called `display_HD44780_init()`. The function provides basic setup of the display. Before using this function, you must call the function `i2c_hal_intialization()`.
* Another important functions is `display HD44780 cmd()`, which writes specific command to the HD44780. List of command is placed in the HD44780.h.
