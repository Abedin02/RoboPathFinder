#include<stdio.h>
#include<bcm2835.h>
#include"I2C.h"
#include"PWM.h"
#include "math.h"


void PWMInit(unsigned int address){
    Adafruit_I2C(address);
    setAllPWM(0, 0);
    write8(__MODE2, __OUTDRV);
    write8(__MODE1, __ALLCALL);
    delay(0.005);
    unsigned int mode1 = readU8(__MODE1);
    mode1 = (mode1 & ~__SLEEP );               
    write8(__MODE1, mode1);
    delay(0.005); 
    mode1 = readU8(__MODE1);
    mode1 = mode1 = mode1 & ~(__SLEEP);
    write8(__MODE1, mode1);
    bcm2835_delay(5000);
}


void setPWMFreq(int freq) {
    // Sets the PWM frequency
    float prescaleval = 25000000.0;    // 25MHz
    prescaleval /= 4096.0;             // 12-bit
    prescaleval /= (float)freq;
    prescaleval -= 1.0;
    int oldmode = readU8(__MODE1);
    int newmode = (oldmode & 0x7F) | 0x10;  // sleep
    write8(__MODE1, newmode);         // go to sleep
    write8(__PRESCALE, (int) prescaleval);
    write8(__MODE1, oldmode);
    bcm2835_delay(0.005);
    write8(__MODE1, (oldmode | 0x80));
}


void setPWM(int channel, int on, int off){
    write8(__LED0_ON_L + 4 * channel, (on & 0xFF));
    write8(__LED0_ON_H + 4 * channel, (on >> 8));
    write8(__LED0_OFF_L + 4 * channel, (off & 0xFF));
    write8(__LED0_OFF_H + 4 * channel, (off >> 8));

}


void setAllPWM(int on, int off){
    write8(__ALL_LED_ON_L, (on & 0xFF));
    write8(__ALL_LED_ON_H, (on >> 8));
    write8(__ALL_LED_OFF_L, (off & 0xFF));
    write8(__ALL_LED_OFF_H, (off >> 8));

}
