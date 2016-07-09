/* Driver for HD44780 using I2C 8-bit parallel expander PCF8574A
 * David Hladky
 * 2016
 * Version 1.1 Update 8-7-2016
 */

/* Connections HD44780 with I2C expander PCF8574A.
 * P0 - RS
 * P1 - RW
 * P2 - E
 * P3 - Q1 - backlight
 * P4 - D4
 * P5 - D5
 * P6 - D6
 * P7 - D7
 * */

#include "HD44780.h"

void display_HD44780_init()
{
    uint8_t first_init_data[] = {0x3C,0x38}; // First combination of initialization commands for 4 bit mode.
    uint8_t set_4_bit[] = {0x2C,0x28}; // Function set to 4 bit mode.

    HAL_Delay(20); // Start display wait for 20ms.
    HAL_I2C_Master_Transmit(&I2C1_struct,I2C_dev_add,first_init_data,2,1000); // D4 - 1, D5 - 1, D6 - 0, D7 - 0; Q1 - on
    HAL_Delay(4); // Delay 4ms
    HAL_I2C_Master_Transmit(&I2C1_struct,I2C_dev_add,first_init_data,2,1000); // D4 - 1, D5 - 1, D6 - 0, D7 - 0; Q1 - on
    HAL_Delay(1); // Delay 4ms
    HAL_I2C_Master_Transmit(&I2C1_struct,I2C_dev_add,first_init_data,2,1000); // D4 - 1, D5 - 1, D6 - 0, D7 - 0; Q1 - on
    HAL_I2C_Master_Transmit(&I2C1_struct,I2C_dev_add,set_4_bit,2,1000); //Setup display to the 4 bit mode

    display_HD44780_cmd(DISPLAY_SET); // Setting the display to the 4 bit mode with two rows.
    display_HD44780_cmd(ENTER_MODE); // Shift the cursor and text to the right - increment mode.
    display_HD44780_cmd(DISPLAY_ON); // Display ON.

    HAL_Delay(5); //Delay 5ms

    display_HD44780_cmd(DISPLAY_CLEAR); // Clear display

}

void display_HD44780_cmd(uint8_t cmd)
{
    uint8_t data_to_disp[4];

    data_to_disp[0] = (cmd & 0xF0)| 0x0C; // Send 4 upper bits of command - set E to 1
    data_to_disp[1] = (cmd & 0xF0)| 0x08; // Send 4 upper bits of command - set E to 0
    data_to_disp[2] = (cmd << 4)| 0x0C; // Send 4 lower bits of command - set E to 1
    data_to_disp[3] = (cmd << 4)| 0x08; // Send 4 lower bits of command - set E to 0

    if ((cmd == 1) || (cmd == 2))
    {
        HAL_I2C_Master_Transmit(&I2C1_struct,I2C_dev_add,data_to_disp,4,1000); //Send the Command to the display.
        HAL_Delay(2); // Delay2ms.
    }

    else
    {
        HAL_I2C_Master_Transmit(&I2C1_struct,I2C_dev_add,data_to_disp,4,1000); //Send the Command to the display.
    }

}

void display_HD44780_data(uint8_t data)
{
    uint8_t data_to_disp[4];

    data_to_disp[0] = (data & 0xF0)| 0x0D; // Send 4 upper bits of data - set E to 1, set RS to 1
    data_to_disp[1] = (data & 0xF0)| 0x09; // Send 4 upper bits of data - set E to 0, set RS to 1
    data_to_disp[2] = (data << 4)| 0x0D; // Send 4 lower bits of data - set E to 1, set RS to 1
    data_to_disp[3] = (data << 4)| 0x09; // Send 4 lower bits of data - set E to 0, set RS to 1

    HAL_I2C_Master_Transmit(&I2C1_struct,I2C_dev_add,data_to_disp,4,1000); //Send data to the display.
}

int8_t display_HD44780_write_char(char c, uint8_t row, uint8_t position)
{
    volatile uint8_t address_DDRAM = 0;

    if (position > 16) return -1; // Number of char per row is 16, if the number is greater then 16 return -1.

    if (row == 1)
    {
        address_DDRAM = (0x00 + position - 1) | 0x80; // Set the address in DDRAM.
        display_HD44780_cmd(address_DDRAM);
        display_HD44780_data(c); // Write data to the SDRAM address.
    }

    else if (row == 2)
    {
        address_DDRAM = (0x40 + position - 1) | 0x80; // Set the address in DDRAM.
        display_HD44780_cmd(address_DDRAM);
        display_HD44780_data(c); // Write data to the SDRAM address.
    }

    else // Display have only 2 rows, return error.
    {
        return -1;
    }
    return 0;
}

int8_t display_HD44780_write_string_position(char *str, uint8_t row, uint8_t position)
{
    uint8_t address_DDRAM = 0;
    uint8_t counter;

    if (position > 16) return -1; // Number of char per row is 16, if the number is greater then 16 return -1

    if (row == 1)
    {
        address_DDRAM = (0x00 + position - 1) | 0x80; // Set the address in DDRAM
        display_HD44780_cmd(address_DDRAM);
        counter = position; // Setup counter

        while(*str != '\0')
        {
            if(counter > 0x10) return -1; // The first row has reach the end of memory.
            counter++;
            display_HD44780_data(*str++); // Write data to the SDRAM address.
        }
    }

    else if (row == 2)
    {
        address_DDRAM = (0x40 + position - 1) | 0x80; // Set the address in DDRAM.
        display_HD44780_cmd(address_DDRAM);
        counter = 0x40 + position; // Setup counter

        while(*str != '\0')
        {
            if(counter > 0x50) return -1; // The second row has reach the end of memory.
            counter++;
            display_HD44780_data(*str++); // Write data to the SDRAM address.
        }
    }

    else // Display have only 2 rows, return error.
    {
        return -1;
    }

    return 0;
}


int8_t display_HD44780_write_string(char *str)
{
    uint8_t counter = 0;

    display_HD44780_cmd(0x80); // Set the address in DDRAM

    while(*str != '\0')
    {
        if(counter == 16) display_HD44780_cmd(0xC0); // Continue on a new row.
        else if (counter > 31) return -1; // Max 32 characters will be written.
        counter++;
        display_HD44780_data(*str++); // Write data to the SDRAM address.
    }

    return 0;
}

int8_t display_HD44780_write_custom_char(uint8_t *custom_char, uint8_t address_of_char)
{
	uint8_t counter = 0;

	if (address_of_char > 0x3F) return -1; // Last address in CGRAM is 0x3F

	address_of_char |= 0x40;
	display_HD44780_cmd(address_of_char); // Set the address in DDRAM

	for(counter = 0; counter < 8; counter ++) // Maximum rows per characters is 8
	{
		display_HD44780_data(*custom_char++); // Load custom into the display
	}

	return 0;
}


