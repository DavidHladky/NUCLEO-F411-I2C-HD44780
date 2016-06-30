/* Example of using HD44780 driven by the I2C IO expander.
 * David Hladky
 * 2016
 * Version 1.0 Update 30.6.2016
 */


/*-----------Include files-----------*/

#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "HD44780.h"
#include "i2c_hal.h"


int main(void)
{

	HAL_Init(); // Initialization HAL library and system.

	i2c_hal_intialization(); // Initialization I2C peripherals MCU.

	display_HD44780_init(); // HD44780 initialization after initialization I2C peripherals.


	while (1)
		{
			display_HD44780_cmd(DISPLAY_CLEAR); // Clear display

			display_HD44780_write_string_position("Hello World!", 1, 1); // Write at first row and position string Hello World!
			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_CLEAR);

			display_HD44780_write_string_position("Hello World!", 2, 3);
			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_CLEAR);

			display_HD44780_write_string("For all fans STM32! For all fans STM32!"); // Fills the entire display by the text.
			HAL_Delay(2000); // Delay 2 second

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(TEXT_SHIFT_RIGHT); // Shift text to the right

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(TEXT_SHIFT_LEFT); // Shift text to the left.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_CLEAR);

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_ON); // On cursor.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_SHIFT_RIGHT); // Cursor shift to the right.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_SHIFT_LEFT); // Cursor shift to the left.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_BLINKING_ON); // Start blinking of cursor.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_OFF);

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_ON);
		}
}
