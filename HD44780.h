/*------------------------ Include files ------------------------*/

#include "stm32f4xx_hal.h"
#include "i2c_hal.h"

/*----------------------- Definitions cmd -----------------------*/

#define DISPLAY_CLEAR			0x01
#define	DISPLAY_SET			0x28
#define	DISPLAY_ON			0x0C
#define DISPLAY_OFF			0x08
#define CURSOR_ON			0x0E
#define CURSOR_OFF			0x0C
#define CURSOR_BLINKING_ON		0x0F
#define CURSOR_BLINKING_OFF		0x0E
#define	CURSOR_SHIFT_LEFT         0x10
#define	CURSOR_SHIFT_RIGHT		0x14
#define ENTER_MODE              0x06
#define TEXT_CURSOR_HOME		0x02
#define TEXT_SHIFT_LEFT			0x18
#define TEXT_SHIFT_RIGHT		0x1C

/*---------- Definitions of address if custom character ----------*/

#define CUSTOM_CHAR_1			0x00
#define	CUSTOM_CHAR_2			0x08
#define	CUSTOM_CHAR_3			0x10
#define CUSTOM_CHAR_4			0x18
#define	CUSTOM_CHAR_5			0x20
#define	CUSTOM_CHAR_6			0x28
#define	CUSTOM_CHAR_7			0x30
#define	CUSTOM_CHAR_8			0x38

/*-------------- Definitions addresses of PCF8574A ---------------*/

#define I2C_dev_add	0x7E

/*-------------------------- Functions --------------------------*/

void display_HD44780_init(); // Initialization of HD44780

void display_HD44780_cmd(uint8_t cmd_to_disp); // Send the command to the HD44780

void display_HD44780_data(uint8_t data); // Write the data to the memory of HD44780

int8_t display_HD44780_write_char(char c, uint8_t row, uint8_t position); // Write a character to a specific position; maximum number of rows is 2; range of number for position is from 1 to 16.

int8_t display_HD44780_write_string(char *str); // Write a string to the display.

int8_t display_HD44780_write_string_position(char *str, uint8_t row, uint8_t position); // Write a string to a specific position.

int8_t display_HD44780_write_custom_char(uint8_t *custom_char, uint8_t address_of_char); // Write a custom character into the display.
