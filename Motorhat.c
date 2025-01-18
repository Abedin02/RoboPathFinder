#include <stdio.h>
#include <bcm2835.h>
#include "MotorHat.h"
#include "PWM.h"

motor motors[4];

void initMotors() {
    motors[0].pwm = 8;
    motors[0].in1 = 9;
    motors[0].in2 = 10;

    motors[1].pwm = 13;
    motors[1].in1 = 12;
    motors[1].in2 = 11;

    motors[2].pwm = 2;
    motors[2].in1 = 3;
    motors[2].in2 = 4;

    motors[3].pwm = 7;
    motors[3].in1 = 6;
    motors[3].in2 = 5;
}

void run(uint8_t command, uint8_t motorID) {
    if (command == FORWARD) {
        setPin(motors[motorID].in1, 1);
        setPin(motors[motorID].in2, 0);
    } else if (command == BACKWARD) {
        setPin(motors[motorID].in1, 0);
        setPin(motors[motorID].in2, 1);
    } else if (command == RELEASE) {
        setPin(motors[motorID].in1, 0);
        setPin(motors[motorID].in2, 0);
    } else if (command == BRAKE) {
        setPin(motors[motorID].in1, 1);
        setPin(motors[motorID].in2, 1);
    }
}

void initHat(int addr, int freq) {
    initPWM(addr, 1600);
    initMotors();
}

void setPin(uint8_t pin, uint8_t value) {
    if (pin > 15) {
        printf("PWM pin must be between 0 and 15 inclusive\n");
        return;
    }
    setPWM(pin, 0, value ? 4096 : 0);
}

void resetAll(void) {
    resetPWM();
}

void setPWM(int channel, int on, int off) {
    setPWM(channel, on, off);
}

void setAllPWM(int on, int off) {
    setAllPWM(on, off);
}
