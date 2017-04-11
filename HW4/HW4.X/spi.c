#include "spi.h"
#include <math.h>

void setVoltage(char channel, char voltage)
{   
    if (channel == 0) 
    {
        voltage>>4 |= 0x70;
    }
    else if (channel == 1) 
    {
        voltage>>4 |= 0xF0;
    }
    
    CS = 0;
    SPI1_IO(voltage>>4);
    SPI1_IO(voltage<<4);
    CS = 1;
}
void initSPI1()
{
    //Initialize SPI here
    
    SPI1CON = 0;                    // Turn off SPI and reset
    SPI1BUF;                        // Clear buffer
    SPI1BRG = 239;                   // Set baud rate to 100kHz
    
    SPI1STATbits.SPIROV = 0;        // Clear overflow bit
    SPI1CONbits.CKE = 1;            // Data changes when clock goes from high to low (since CKP is 0)
    SPI1CONbits.MSTEN = 1;          
    SPI1CONbits.ON = 1;             // Turn on SPI 1   
    
    TRISBbits.TRISB15 = 0;          // Set B15 as an output pin (SS1 output)
    CS = 1;                         // CS set high
    
    RPB13Rbits.RPB13R = 0b0011;     // B13 - SDO1
    SDI1Rbits.SDI1R = 0b0100;       // B8 - SDI1
}

char SPI1_IO(char write)
{
    SPI1BUF = write;
    while(!SPI1STATbits.SPIRBF) {   // Wait to receive data
        ;
    }
    return SPI1BUF;
}

/*
void sineWave() {
    int i=0;
    for(i=0; i<1000; ++i)
    {
        sine_wave[i]=255*sin(2*M_PI*i/100); 
    }
}


void triangleWave() {
    int i=0;
    for(i=0; i<1000; ++i)
    {
        triangle_wave[i] = (1.275*i); 
    }
}
*/ 