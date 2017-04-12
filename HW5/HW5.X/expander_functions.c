#include<xc.h>           // processor SFR definitions
#include "i2c_master_noint.h"
#include "expander_functions.h"

unsigned char control_byte = 0b01000000;        // Set up control byte (default write)
unsigned char control_byte_read = 0b01000001;   // Set control byte R/W bit as "Read" (1)

unsigned char GPIO_address = 0x09;              // GPIO address, from datasheet
unsigned char OLAT_address = 0x0A;              // OLAT address, from datasheet

void initExpander()
{
    i2c_master_start();                         // I2C master start
    i2c_master_send(control_byte);  
    i2c_master_send(0x00);                      // Send address of IODIR (from datasheet)
    i2c_master_send(0b1000000);                 // Set pin GP7 as input(1), pin GP0 as output(0)
    i2c_master_stop();                          // I2C master stop
}

void setExpander(char pin, char level)
{
    i2c_master_start();                         // I2C master start
    i2c_master_send(control_byte);  
    i2c_master_send(0x0A);                      // Send address of OLAT (from datasheet)
    i2c_master_stop();                          // I2C master stop
}

char getExpander()
{
    char x = 0;
    return x;
    //Something here
}