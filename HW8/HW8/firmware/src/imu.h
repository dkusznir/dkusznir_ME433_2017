#ifndef IMU_H__
#define IMU_H__
// Header file for IMU.c
// implements high-level IMU functions using I2C

#define SLAVE_ADDR 0x6B 

void IMU_init(void);      
unsigned char get_whoami(void);
void i2c_read_multiple(unsigned char addr, unsigned char r, unsigned char * data, int length);

#endif