#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include <math.h>
#include "ILI9163C.h"
#include "i2c_master_noint.h"
#include "imu.h"



int main() 
{

    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    
    // LED output pin 
    TRISAbits.TRISA4 = 0;
    
    // Button input pin
    TRISBbits.TRISB4 = 1;
    
    LATAbits.LATA4 = 0;   
        
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    
    SPI1_init();
    LCD_init();
    
    LCD_clearScreen(BLACK);

    IMU_init();
    
    __builtin_enable_interrupts();
 
    unsigned char whoami = 0;
    whoami = get_whoami();
    
    unsigned char msg[100];  
    unsigned char imu_data[14];

    while(1) 
    {
        unsigned char whoami = 0;
        whoami = get_whoami();

        unsigned char msg[20];
        unsigned char imu_data[14];

        sprintf(msg, "IMU Address: %d", whoami);
        display_string(msg, 2, 2, WHITE, BLACK);

        i2c_read_multiple(SLAVE_ADDR, 0x20, imu_data, 14);

        signed char gyroX = imu_data[4] << 8 | imu_data[3];
        signed char gyroY = imu_data[6] << 8 | imu_data[5];
        signed char gyroZ = imu_data[8] << 8 | imu_data[7];
        signed char accelX = imu_data[10] << 8 | imu_data[9];
        signed char accelY = imu_data[12] << 8 | imu_data[11];
        signed char accelZ = imu_data[14] << 8 | imu_data[13];

        float acc_x = (float)accelX * 0.61;
        float acc_y = (float)accelY * 0.61;

        display_barX(62, 62, ((signed char) (acc_x)), 10, BLUE, BLACK);
        display_barY(62, 62, ((signed char) (acc_y)), 10, WHITE, BLACK);
        
        LCD_clearScreen(BLACK);
    }
    return 0;
}

