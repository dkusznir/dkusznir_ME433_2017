#ifndef SPI__H__
#define SPI__H__

#include <xc.h>

#define CS LATBbits.LATB15

//static volatile char sine_wave[1000];
//static volatile char triangle_wave[1000];

void setVoltage(char channel, char voltage);
void initSPI1();
char SPI1_IO(char write);
//void sineWave();
//void triangleWave();

#endif