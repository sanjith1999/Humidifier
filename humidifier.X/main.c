/*
 * File:   main.c
 * Author: Sanjith
 *
 * Created on December 4, 2022, 4:11 PM
 */
#include <xc.h>
#include "config.h"
#include "i2c.h"
#include "SSD1306.c"      // include SSD1306 OLED display driver source code
#include "GFX_Library.c"  // include graphics library source code


void Configs();

void main(void) {
    Configs();
    TRISA5 = 0;
    I2C_Init(100000);
    SSD1306_begin(SSD1306_SWITCHCAPVCC, 0x3C);
    // init done
    display();
    __delay_ms(2000);

    // clear the buffer.
    display_clear();

    // draw a single pixel
    display_drawPixel(10, 10, WHITE);
    display();
    __delay_ms(2000);
    display_clear();
    RA5 = 1;
    while (1) {
        RA5 = 0;
        __delay_ms(1000);
        RA5 = 1;
        __delay_ms(1000);
    }
    return;
}

void Configs() {
    // Oscillator Selection According to FOSC bits
    SCS1 = 0;
    SCS0 = 0;

    // Internal Frequency: 16 MHz
    OSCCONbits.IRCF3 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;

}
