/* 
 * File:   i2c.h
 * Author: Sanjith
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "config.h"

void I2C_Init(const unsigned long feq_K); //begin I2C as master

void I2C_Wait(void);
void I2C_Begin(void);
void I2C_End(void);

_Bool I2C_Write(unsigned data);
unsigned short I2C_Read(unsigned short ack);    


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

