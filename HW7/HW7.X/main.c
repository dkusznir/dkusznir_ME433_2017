#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include <math.h>
#include "ILI9163C.h"
#include "i2c_master_noint.h"
#include "imu.h"

// DEVCFG0
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = OFF // no boot write protect
#pragma config CP = OFF // no code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll
#pragma config FSOSCEN = OFF // turn off secondary oscillator
#pragma config IESO = OFF // no switching clocks
#pragma config POSCMOD = HS // high speed crystal mode
#pragma config OSCIOFNC = OFF // disable secondary osc
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // do not enable clock switch
#pragma config WDTPS = PS1 // use slowest wdt
#pragma config WINDIS = OFF // wdt no window mode
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#pragma config FUSBIDIO = ON // USB pins controlled by USB module
#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module

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
       int i = 1;
       for (i; i <= 100; i++)
       {
           
           sprintf(msg, "IMU Address: %d", whoami);
           display_string(msg, 5, 5, WHITE, BLACK);
           
           i2c_read_multiple(SLAVE_ADDR, 0x20, imu_data, 14);
           
           signed char gyroX = imu_data[4] << 8 | imu_data[3];
           signed char gyroY = imu_data[6] << 8 | imu_data[5];
           signed char gyroZ = imu_data[8] << 8 | imu_data[7];
           signed char accelX = imu_data[10] << 8 | imu_data[9];
           signed char accelY = imu_data[12] << 8 | imu_data[11];
           signed char accelZ = imu_data[14] << 8 | imu_data[13];
           
           float accX = (float)(accelX)*0.061*1000;
           float accY = (float)(accelY)*0.061*1000;

           display_barX(62, 62, YELLOW, BLACK, ((signed char) (accX)), 5);
           display_barY(62, 62, BLUE, BLACK, ((signed char) (accY)), 5);
       
       }
       LCD_clearScreen(BLACK);
    }
    return 0;
}

