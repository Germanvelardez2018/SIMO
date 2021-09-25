#include "simo/lcd.h"
#include <string.h>
#include "simo/i2c.h"
#include "FreeRTOS.h"
#include "task.h"


#include "pico/stdlib.h"
#define i2c_default        S_I2C0
#define VDELAY              1
#define DELAY_US            60





static void inline lcd_char(char val) {
    lcd_send_byte(val, LCD_CHARACTER);
}


void i2c_write_byte(uint8_t val) {

  
    s_i2c_write(i2c_default, LCD_ADDRESS, &val, 1, false);

}

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work

    
   // vTaskDelay(VDELAY);
   // sleep_us(DELAY_US);
    
    i2c_write_byte(val | LCD_ENABLE_BIT);
   // sleep_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
   // sleep_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int line, int position) {
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    lcd_send_byte(val, LCD_COMMAND);
}



void lcd_string(const char *s) {
    while (*s) {
        lcd_char(*s++);
    }
}

void lcd_init() {
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}




void lcd_task(void* params)
{

    s_i2c_init(i2c_default,(100*1000));
    lcd_init();
    static char *message[] =
            {
                    "RP2040 by", "Raspberry Pi",
                    "A brand new", "microcontroller",
                    "Twin core M0", "Full C SDK",
                    "More power in", "your product",
                    "More beans", "than Heinz!"
            };



    while (1) 
    {
        vTaskDelay(200);
      
      
        for (int m = 0; m < sizeof(message) / sizeof(message[0]); m += MAX_LINES) {
            for (int line = 0; line < MAX_LINES; line++) 
            {
                lcd_set_cursor(line, (MAX_CHARS / 2) - strlen(message[m + line]) / 2);
                lcd_string(message[m + line]);
            }
            
            vTaskDelay(2000);
            lcd_clear();
        }
    
    }
}

