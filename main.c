/* Example of using HD44780 driven by the I2C IO expander.
 * David Hladky
 * 2016
 * Version 1.1 Update 8-7-2016
 */


/*-----------Include files-----------*/

#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "HD44780.h"
#include "i2c_hal.h"

uint8_t custom_char1[] = {0xe,0x1b,0x11,0x11,0x11,0x11,0x1f};	// Empty Battery
uint8_t custom_char2[] = {0xe,0x1b,0x11,0x11,0x11,0x1f,0x1f}; 	// Low Battery
uint8_t custom_char3[] = {0xe,0x1b,0x11,0x1f,0x1f,0x1f,0x1f}; 	// Half Battery
uint8_t custom_char4[] = {0xe,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}; 	// Full Battery

int main(void)
{

	HAL_Init(); // Initialization HAL library and system.

	i2c_hal_intialization(); // Initialization I2C peripherals MCU.

	display_HD44780_init(); // HD44780 initialization after initialization I2C peripherals.

	display_HD44780_write_custom_char(custom_char1, CUSTOM_CHAR_1); // Write a custom characters on 1 position of CGRAM

	display_HD44780_write_custom_char(custom_char2, CUSTOM_CHAR_2); // Write a custom characters on 2 position of CGRAM

	display_HD44780_write_custom_char(custom_char3, CUSTOM_CHAR_3); // Write a custom characters on 3 position of CGRAM

	display_HD44780_write_custom_char(custom_char4, CUSTOM_CHAR_4); // Write a custom characters on 4 position of CGRAM

	while (1)
		{

			display_HD44780_write_string_position("Hello World!", 1, 1); // Write at first row and position string Hello World!
			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_CLEAR);

			display_HD44780_write_string_position("Hello World!", 2, 3);
			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_CLEAR);

			display_HD44780_write_string("For all fans STM32! For all fans STM32!"); // Fills the entire display by the text.
			HAL_Delay(2000); // Delay 2 second

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(TEXT_SHIFT_RIGHT); // Shift the text to the right

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(TEXT_SHIFT_LEFT); // Shift the text to the left.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_CLEAR);

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_ON); // On cursor.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_SHIFT_RIGHT); // Shift the cursor to the right.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_SHIFT_LEFT); // Shift the cursor to the left.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_BLINKING_ON); // Start blinking of cursor.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_BLINKING_OFF); // Start blinking of cursor.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(CURSOR_OFF); // OFF cursor.
			display_HD44780_write_string_position("Custom characters:", 1, 1);
			display_HD44780_write_char(0, 2, 1); // Display the custom character1 on the display.
			display_HD44780_write_char(1, 2, 2); // Display the custom character2 on the display.
			display_HD44780_write_char(2, 2, 3); // Display the custom character3 on the display.
			display_HD44780_write_char(3, 2, 4); // Display the custom character4 on the display.

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_OFF);

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_ON);

			HAL_Delay(2000); // Delay 2 second
			display_HD44780_cmd(DISPLAY_CLEAR);
		}
}
