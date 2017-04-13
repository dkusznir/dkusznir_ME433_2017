#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "i2c_master_noint.h"
#include "expander_functions.h"

#define SLAVE_ADDRESS_WRITE 0b01000000          // Slave write defined: Least sig bit = 0
#define SLAVE_ADDRESS_READ  0b01000001          // Slave read define: Least sig bit = 1

void initExpander()
{
    //Turn off analog for I2C2 pins, B2 & B3 (make them digital)
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    
    i2c_master_start();                                 // I2C master start
    
    i2c_master_send(SLAVE_ADDRESS_WRITE);               // Write operation
    i2c_master_send(0x00);                              // Set up IODIR
    i2c_master_send(0b10000000);                        // Set pin GP7 as input(1), pin GP0 as output(0), others output (0)
    
    i2c_master_stop();                                  // I2C master stop
}

void setExpander(char pin, char level)
{
    
    char status = getExpander();

    if (level == 0) 
    {
        status &= ~(1 << pin);            
    }
    
    else 
    {
        status |= (1 << pin);               
    }
 
    i2c_master_start();                                 // I2C master start
    
    i2c_master_send(SLAVE_ADDRESS_WRITE);               // Write operation
    i2c_master_send(0x0A);                              // Send to OLAT
    i2c_master_send(status);                            // Send requested pin level
    
    i2c_master_stop();                                  // I2C master stop
}

char getExpander()
{
    i2c_master_start();                                 // I2C master start
    i2c_master_send(SLAVE_ADDRESS_WRITE);               // Write operation
    i2c_master_send(0x09);                              // GPIO
    
    i2c_master_restart();                               // Restart
    
    i2c_master_send(SLAVE_ADDRESS_READ);                // Read operation
    unsigned char data_received = i2c_master_recv();    // Get data (character)
    
    i2c_master_ack(1);                                  // Acknowledged = 1, no more data requested
    i2c_master_stop();                                  // I2C master stop
    
    return data_received;

}
