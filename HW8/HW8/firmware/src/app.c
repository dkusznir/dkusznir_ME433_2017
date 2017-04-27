#include "app.h"
#include "ILI9163C.h"
#include "i2c_master_noint.h"
#include "imu.h"
#include <sys/attribs.h> // __ISR macro
#include <math.h>
#include <stdio.h>

APP_DATA appData;

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    // LED output pin 
    TRISAbits.TRISA4 = 0;
    
    // Button input pin
    TRISBbits.TRISB4 = 1;
    
    LATAbits.LATA4 = 0;   
        
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;

    SPI1_init();
    LCD_init();
    IMU_init();
    
    LCD_clearScreen(BLACK);


}

void APP_Tasks(void) {

    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized) {

                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            _CP0_SET_COUNT(0);
            LATAbits.LATA4 = 1;

            while(_CP0_GET_COUNT() < 12000) //12000 in order to obtain 1KHz
            {
                // Button pressed
                while(!PORTBbits.RB4)
                {
                    // Turn off LED
                    LATAbits.LATA4 = 0;
                }

            }

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

           break;
        }

            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}