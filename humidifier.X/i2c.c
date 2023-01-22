#include "i2c.h"

void I2C_Init(const unsigned long feq_K) //Begin IIC as master
{
    SSP1CON1 = 0b00101000;
    SSP1CON2 = 0;
    INTCONbits.GIE = 1;
    PIR1bits.SSP1IF = 1;
    SSP1CON3bits.SCIE = 1;
    SSP1CON3bits.PCIE = 1;

    SSP1ADD = (_XTAL_FREQ / (4 * feq_K)) - 1;
    SSP1STAT = 0;
    ANSELC = 0x00;
    TRISC0 = 1; //SCL
    TRISC1 = 1; //SDA
}

void I2C_Wait() {
    while ((SSP1CON2 & 0b00011111) || (SSP1STAT & 0b00000100)); //check this on registers to make sure the IIC is not in progress
}

void I2C_Begin() {
    I2C_Wait(); //Hold the program is I2C is busy 
    SEN = 1; //Begin IIC
    while(SEN);
}

void I2C_End() {
    I2C_Wait(); //Hold the program is I2C is busy 
    PEN = 1; //End IIC 
    while(PEN);
}

_Bool I2C_Write(unsigned data) {
    I2C_Wait(); //Hold the program is I2C is busy
    SSP1BUF = data;
    SSP1IF = 0;
    while(!SSP1IF);
    return ACKSTAT;
}

unsigned short I2C_Read(unsigned short ack) {
    unsigned short incoming;
    I2C_Wait();
    RCEN = 1;
    I2C_Wait();
    incoming = SSPBUF; //get the data saved in SSPBUF

    I2C_Wait();
    ACKDT = (ack) ? 0 : 1; //check if ACK bit received 
    ACKEN = 1;

    return incoming;
}
