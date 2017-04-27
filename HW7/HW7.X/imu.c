#include <xc.h>
#include "imu.h"
#include "i2c_master_noint.h"

void IMU_init(void)
{
    
    i2c_master_setup();                     // Init I2C 
    
    i2c_master_start();                     
    i2c_master_send(SLAVE_ADDR << 1 | 0);   // Send slave address left shifted by 1 (write)
    i2c_master_send(0x10);                  // CTRL1_XL register address: 0x10
    i2c_master_send(0x82);            // 1.66 kHz, 2g sensitivity, 100 Hz filter
    i2c_master_stop();
     
    i2c_master_start();                     
    i2c_master_send(SLAVE_ADDR << 1 | 0);   // Send slave address left shifted by 1 (write) 
    i2c_master_send(0x11);                  // CTRL2_G register address: 0x11
    i2c_master_send(0x88);            // 1.66 kHz, 1000 dps sensitivity
    i2c_master_stop();

    i2c_master_start();                     
    i2c_master_send(SLAVE_ADDR << 1 | 0);   // Send slave address left shifted by 1 (write) 
    i2c_master_send(0x12);                  // CTRL3_C register address: 0x12
    i2c_master_send(0x04);                 
    i2c_master_stop(); 
                     
}

unsigned char get_whoami(void)
{
    unsigned char whoami;
    
    i2c_master_start();                     
    i2c_master_send(SLAVE_ADDR << 1 | 0);   // Send slave address left shifted by 1 (write)                                          
    i2c_master_send(0x0F);                  // Whoami register address: 0x0F
    
    i2c_master_restart();                   // Restart I2C
    
    i2c_master_send((SLAVE_ADDR << 1)|1);   // Send slave address left shifted by 1, lsb = 1 (read)
    whoami = i2c_master_recv();             // Receive a byte from slave
    i2c_master_ack(1);                      // No more bytes requested
    i2c_master_stop();                     
    
    return whoami;
    
}

void i2c_read_multiple(unsigned char addr, unsigned char r, unsigned char * data, int length)
{
    int i;

    i2c_master_start();                     
    i2c_master_send(addr << 1 | 0);         // Send slave address left shifted by 1 (write) 
    i2c_master_send(r);                     
    i2c_master_restart();                   // Restart I2C
    i2c_master_send((addr << 1) | 1);       // Send the slave address left shifted by 1 and 1 in lsb (read)
    
    for(i = 0; i <= length; i++)
    {
        data[i] = i2c_master_recv();        // Receive a byte from slave
        
        if(i < length)
        {
            i2c_master_ack(0);              // More bytes requested
        }
        
        else
        {
            i2c_master_ack(1);              // Done with request
        }
    }
    
    i2c_master_stop();                      
}
