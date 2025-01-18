#include "Robot.h"
#include "I2C.h"
#include "MotorHat.h"
#include "Servo.h"
#include "PWM.h"
#include "math.h"


#define LEFT_TRIM = 0;
#define RIGHT_TRIM = 0;

int main(argc, argv){
    RobotInit();
    robot.forward(150, 1.0);
    robot.left(200, 0.5);
    robot.forward(150, 1.0);
    robot.left(200, 0.5);
    robot.forward(150, 1.0);
    robot.left(200, 0.5);
    robot.forward(150, 1.0);
    robot.right(200, 0.5);
    robot.right(100);
    bcm2835_delay(2000);
    robot.stop();
    robot.backward(150, 1.0);
    robot.right(200, 0.5);
    robot.backward(150, 1.0);
    robot.right(200, 0.5);
    robot.backward(150, 1.0);
    robot.right(200, 0.5);
    robot.backward(150, 1.0);
    return 0;
    }
